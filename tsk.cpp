#include "tsk.hpp"

#include <string>       // for string
#include <sstream>
#include <ctime>        // for getting time when file is creating or is editing
#include <vector>

#include <fstream>      // for working with files

//using namespace tsk;
using namespace std;

namespace tsk{

#define TSK_FOLDER_PATH         "dat/"          // folder is located in user's folder, contains task-files 
#define METADATA_REGION_BEGIN   "[METADATA]"    // 'Header' of metadata in task-file 
#define MAIN_PART_REGION_BEGIN  "[MAIN-PART]"   // 'Header' of main part in task-file 

// If file version higher then editor's and it is not able to be opened 
#define ERR_VER_TITLE_TEXT "Uncnown version"
#define ERR_VER_TEXT_TEXT "File version is unknown, it's unable to read it\nVersion is higher then expected\nCurrent version - "

#pragma region Protection of data

// to generate a KEY gets a hash of input parameter
string generKey(const string& parameter_for_KEY_generating){
        hash<string>    hasher;
        size_t          hashed  = hasher(parameter_for_KEY_generating);                       
        return          std::to_string(hashed).std::string::substr(0, 16);
}

#if ENCODE_VER == 1 // do not uses any encryption

string encryptData(const string& input){
        return          input;
}
string decryptData(const string& input, const string& key){

        return          input;
}

#elif ENCODE_VER == 2 // uses an XOR encryption

string encryptData(const string& input, string KEY){
        int             input_length    = input.length();
        int             lenght_of_key   = 16;
        string          result;
        
        for (int i = 0; i < input_length; i++ ){
                result[i]       = input[i] ^ KEY[i % lenght_of_key];
        }
        return          result;
}

string encryptData(const string& input){
        int             input_length    = input.length();
        int             lenght_of_key   = 16;
        string          KEY             = generKey(input.substr(input_length, lenght_of_key)); 
        string          result;

        for (int i = 0; i < input_length; i++ ){
                result[i]       = input[i] ^ KEY[i % lenght_of_key];
        }
        return          result;
}

string decryptData(const string& input, const string& KEY){
        return encryptData(input, KEY);
}

#elif ENCODE_VER == 3 // uses an AES encryption

string encryptData(const string& input){
        string result;
        return          result;
}
string decryptData(const string& input){
        string result;
        return          result;
}

#else // do not uses any enryption

string encryptData(const string& input){
        return          input;
}
string decryptData(const string& input){
        return          input;
}

#endif

#pragma endregion


#pragma region SAVE TO FILE FUNC

void saveIntoFile(string name, string data){
        
        const char* dat = data.c_str();

        int data_size = (char)sizeof(dat);
        
        ofstream file(TSK_FOLDER_PATH + name + EXTENCION, ios::binary);
        if (file.is_open()){
                file.write(dat, data_size);
                file.close();
        }
        else{
                exit(1);
        }
}

void saveFile(string name, string metaData, string mainPart){
        string mainData;

#if ENCODE_VER == 1
        mainData = mainPart;
#else
        mainData = encryptData(mainPart);
#endif
        string _Data =  METADATA_REGION_BEGIN   + metaData + 
                        MAIN_PART_REGION_BEGIN  + mainData;

        saveIntoFile(name, _Data);
}

void saveFile(string name, flMetadata metaData, flText mainPart){
        
        string _MetaData = metaData.to_str();
        string _MainPart = mainPart.to_str();

        saveFile(name, _MetaData, _MainPart);

}

#pragma endregion

#pragma region READ FILE FUNC

flMetadata ReadMetaData(stringstream& file){
        
        vector<string> lns; // keep inside itself all 'metadata' files
        flMetadata metadata;

        string line;
        while (getline(file, line)){
                if(line == METADATA_REGION_BEGIN){
                        continue;
                }
                if(line != MAIN_PART_REGION_BEGIN && line != METADATA_REGION_BEGIN){
                        lns.push_back(line);
                }
                else if (line == MAIN_PART_REGION_BEGIN){
                        break;
                }
                else{
                        break;
                }
        }

        metadata.setMetadata(
                lns[0],
                lns[1],
                lns[2],
                lns[3],
                lns[4],
                lns[5]
        );
        return metadata;
}

flText ReadMainPart(stringstream& file, string _key, int _version){
        vector<string> lines;
        flText text;

        string _inp_file;
        if (_version == 0.1){
                _inp_file = file.str(); 
        }
#if ENCODE_VER > 1
        else {
                _inp_file = decryptData(file.str(), _key);
        }
#endif
        if (_version <= VER){
                stringstream _file;
                _file << _inp_file;
        
                string line;
                while(getline(_file, line)){
                        if(line != MAIN_PART_REGION_BEGIN){
                                continue;
                        }
                        if(line == MAIN_PART_REGION_BEGIN){
                                continue;
                        }
                        else{
                                lines.push_back(line);
                        }
                }
        
                string _title;
                string _text;
        
                _title = lines[0];
                _text = "";
                
                for (int i = 1; i < lines.size(); i++){
                        _text += lines[i] + "\n";
                }
        
                text.setTitle(_title);
                text.setText(_text);
        
        }
        else {
                string ErrText = 
                ERR_VER_TEXT_TEXT               + to_string(VER) + 
                "\nFile format version - "      + to_string(_version);
                
                text.setTitle(ERR_VER_TITLE_TEXT);
                text.setText(ErrText);
        }
        return text;
}

flTask readFile(string name){
        flTask          TASK;
        flMetadata      metaData;
        flText          taskText;

        ifstream        file(TSK_FOLDER_PATH + name, ios::binary);

        stringstream stream;
        stream << file.rdbuf();

        if (file.is_open()){
                metaData        = ReadMetaData(stream);
                taskText        = ReadMainPart(stream, metaData.key, atoi(metaData.version.c_str()));
        }

        TASK.setTask(metaData, taskText);
        
        return TASK;
}

#pragma endregion

#pragma region CLASS FUNCTIONS

void Task::SaveToTskFile(const std::string& input_dat){

}

void Task::EditTskFile(const std::string& input_dat){

}

void Task::ReadFromTskFile(const std::string& name, flTask& data){
        data = readFile(name);
}

#pragma endregion
}
