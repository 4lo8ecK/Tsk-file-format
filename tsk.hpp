// .tsk file is file for saving tasks and notes
// at first, this type saves different types of data using one file

// I am going to make this 'tsk' lib a header-only

/*
        ".tsk" file structure

       
        
        1. 'metadata':
                1. 'version of format'

                2. 'key for decrypting file' - one of some keys.
                        (Using this key you're not able to decrypt file - this key is saved as encrypted
                        also, key is generating usning some data of the task
                        it means for every task key will be unic)
                3. username
                4. file creation date-time
                5. file last editing date-time
                6. task type
        
        2. 'task':
                1. title
                2. such text of task or note
                        (at first time it will be saved as simple text
                        after - as RTF)
*/

#pragma onse

#include <string>

#define EXTENCION ".tsk"  // Task-file Extencion
#define VER 0.1                 // Version of the file format '0.1' - task-text is not encrypted, '0.2' - task-text is encrypting using 'xor' (change this value if something global is changed and it will work only using new version, but it have to be able to open and edit old versions of format)
#define ENCODE_VER 2    // this vallue = VER*10 until 3

namespace tsk{

        #pragma region Types defineings for working with Task files 
        // defineings of special data types
        struct flDate{
                int day;
                int month;
                int year;

                flDate set(int _Day, int _Mon, int _Year){
                        day     = _Day;
                        month   = _Mon;
                        year    = _Year;
                }
                std::string str(){
                        return{
                                std::to_string(day)     +"."+
                                std::to_string(month)   +"."+
                                std::to_string(year)
                        };
                }
                flDate to_date(std::string _date){
                        std::string _day, _mon, _year;

                        _day    = _date.substr(0, 1);
                        _mon    = _date.substr(3, 4);
                        _year   = _date.substr(6, 9);

                        day     = atoi(_day.c_str());
                        month   = atoi(_mon.c_str());
                        year    = atoi(_year.c_str());

                }

        };

        struct flMetadata {
                std::string     version = std::to_string(VER);
                std::string     key;
                std::string     username;
                flDate          creation_date;
                flDate          last_edit_date;
                std::string     tasktype;

                std::string to_str(){
                        return {
                                username                + '\n' +
                                creation_date.str()     + '\n' +
                                last_edit_date.str()    + '\n' +
                                tasktype
                        };
                }
                // functions
                flMetadata setMetadata(
                        std::string     Version,
                        std::string     Key,
                        std::string     Username,
                        std::string     Creation_Date,
                        std::string     Last_Edit_Date,
                        std::string     TaskType
                ){
                        version         = Version;
                        key             = Key; 
                        username        = Username;
                        creation_date.  to_date(Creation_Date);
                        last_edit_date. to_date(Last_Edit_Date);
                        tasktype        = TaskType;
                }

                flMetadata setUsername(std::string input){
                        username        = input;
                }
                flMetadata setCreatDate(flDate input){
                        creation_date   = input;
                }
                flMetadata setLastEditDate(flDate input){
                        last_edit_date  = input;
                }
                flMetadata setTaskType(std::string input){
                        tasktype        = input;
                }

        };
        
        // such type for text
        // maybe in future will be added more things
        struct flText {
                std::string     title;
                std::string     saved_text;
                
                // functions

                std::string to_str(){
                        return {
                                title + '\n' +
                                saved_text
                        };
                }

                flText setText(
                        std::string     Title,
                        std::string     Text
                )
                {
                        title           = Title;
                        saved_text      = Text;
                }
                
                flText setText(std::string Text){
                        saved_text      = Text;
                }
                flText setTitle(std::string Title){
                        title           = Title;
                }

        };

        // main task structure 
        struct flTask{
                flMetadata      metadata;
                flText          text;

                std::string to_str(){
                        return {
                                metadata.to_str()       + '\n' +
                                text.to_str()
                        };
                }
                flTask setTask(
                        flMetadata      MetaData,
                        flText          Text
                ){
                        metadata        = MetaData;
                        text            = Text;
                } 
        };
        #pragma endregion

        class Task{
                // solution of tsk format

                // .tsk file type structure as data type:
                // such type for metadata
#if 0
        public:
                std::string SavePath            = "/";  // as default data saves in executable's dir
                std::string TasksFolderName     = "/tsks/";
#endif
        public:

                void SaveToTskFile(const flTask& input_dat); // to save new file

                void EditTskFile(const std::string& _name, const flTask& input_dat); // to edit exist file

                void ReadFromTskFile(const std::string& _name, flTask& data);
                flTask ReadFromTskFile(const std::string& _name);
        };
}
