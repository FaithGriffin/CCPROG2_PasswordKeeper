/*12037893 Griffin, Faith (S17)

*This version will only work with Windows because of the included windows library header file
that was used for the changeTextColor() function
*Included ASCII artworks were based from ascii artworks from https://ascii.co.uk/art/key
*The changeTextColor() function was based from this website: shorturl.at/dns28 */

#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>

#define COMMONFILE "PWKeeperCommonFile.dat"

typedef struct personStr{
    char username[100];
    char password[100];
    char filename[100];
}personStr;

typedef struct personInt{
    int username[100];
    int password[100];
    int filename[100];
}personInt;

typedef struct personalStr{
    char accountName[100];
    char username[100];
    char password[100];
}personalStr;

typedef struct personalInt{
    int accountName[100];
    int username[100];
    int password[100];
}personalInt;

void changeTextColor(int nColor);
void displayMenu1();
void displayExitMessage();
void displayErrorInput1();
void displayMainMenu();
void decryptCheckPWKeeperFileUsername(personInt read, personStr *decrypted, int key, char usernameNewACcount[]);
void decryptCheckPWKeeperFileFilename(personInt read, personStr *decrypted, int key, char filenameNewACcount[]);
int checkPWKeeperFile(char usernameNewAccount[]);
void stringToInt1(personStr user, personInt *userCopyInt);
void encryptNewAccountInPWKeeperFile(personInt userCopyInt, personStr user);
int isValidFilenameChecker1(personStr user);
int isValidFilenameChecker2(personStr user, int *error);
int isValidFilenameChecker3(personStr user, int *error2);
void createPersonalFile(personStr user);
void decryptPWKeeperLogin(personInt encrypted, personStr *decrypted, int key, personStr loginUser);
int isValidLoginCredentials(personStr *loginUser);
void decryptAcctName(personalStr *decrypted, int key, personalInt user, personalStr loginUserAddPW);
int isUniqueAcctName(personalStr loginUserAddPW, int key, personStr loginUser);
void decryptAllPWFromPersonalFile(personalStr *decrypted, personalInt user, int key);
void displayAllPWFromPersonalFile(personStr loginUser, int key);
void stringToInt2(personalInt *userAddPWCopyInt, personalStr loginUserAddPW);
void encryptNewPWToPersonalFile(int key, personalInt userAddPWCopyInt, personStr loginUser);
int isValidAcctNameAndPW(personalStr loginUserChangePW, int key, personStr loginUser);
void encryptNewPWToPersonalFileWb(int key, personalInt userAddPWCopyInt, personStr loginUser);
void changePW(personalStr loginUserChangePW, int key, personStr loginUser, char loginUserChangePWNewPW[]);
void deletePW(personalStr loginUserDeletePW, int key, personStr loginUser);
void changePWKeeperPW(personStr loginUser, char loginUserChangePWKeeperPWNew[]);

int main()
{
    int nChoiceMenu1, error, error2, key, nOrigin, newActCreated, nChoiceMainMenu, nOrigin2;
    char loginUserChangePWNewPW[100], loginUserChangePWKeeperPWOld[100], loginUserChangePWKeeperPWNew[100];
    personStr user, encryptedUser, loginUser;
    personInt userCopyInt;
    personalStr loginUserAddPW, loginUserChangePW, loginUserDeletePW;
    personalInt userAddPWCopyInt;

    displayMenu1(); //displays PWKeeper Menu (Create New Account/LogIn/Exit)
    changeTextColor(15);
    scanf("%d", &nChoiceMenu1); //asks for input PWKeeper Menu (Create New Account/LogIn/Exit)
    system("cls");
    
    while(nChoiceMenu1 != 0){
        if(nChoiceMenu1 == 1) nOrigin = 1; //user came from CreatePWKeeper Account
        else nOrigin = 2; //user came from LogIn PWKeeper Account
        newActCreated = 0;
        nOrigin2 = 0;
        error = 0;
        error2 = 0;

        if(nChoiceMenu1 == 1){ //Create PWKeeper Account
            while(newActCreated != 1){ //while new PWKeeper Account creation is not successful
                printf("Enter New Username: "); 
                scanf("%s", user.username); //asks for username for new PWKeeper Account
                if(checkPWKeeperFile(user.username) == 0){ //checks PWKeeper Common File --> input username is unique
                    //strcpy(user.username, usernameNewAccount); //copies checked username to username member of struct of type personStr
                    printf("Enter Password: ");
                    scanf("%s", user.password); //asks for pw for new PWKeeper Account
                    printf("Enter Filename (include \".dat\"): ");
                    scanf("%s", user.filename); //asks for filename for new PWKeeper Account
                    while(isValidFilenameChecker1(user) != 1 || isValidFilenameChecker2(user, &error) != 0 || isValidFilenameChecker3(user, &error2) != 1){ //checks if input filename is valid (includes ".dat" and is unique)
                        if(error == 1 || error2 == 1) printf("Oopsie. Invalid input. Change filename :(\n"); //invalid filename input (filename already taken)
                        else printf("Oopsie. Invalid input. Include \".dat\" :(\n"); //invalid filename input (no ".dat")
                        printf("Enter Filename (include \".dat\"): ");
                        scanf("%s", user.filename); //asks for filename for new PWKeeper Account
                        error = 0;
                        error2 = 0;
                    }
                    createPersonalFile(user); //creates new user's personal file
                    stringToInt1(user, &userCopyInt); //copies contents of user(struct personStr) to *userCopyInt(struct personInt)
                    encryptNewAccountInPWKeeperFile(userCopyInt, user); //encrypts new PWKeeper Account to PWKeeper Common File
                    nChoiceMenu1 = 2; //updates nChoiceMenu
                    do{
                        printf("Enter magic number of your choice (remember this number): ");
                        scanf("%d", &key); //asks for key from user
                    }while(key <= 0); //checks if input key is not negative
                    key += strlen(user.username); //adds salt to key
                    newActCreated = 1; //flags new PWKeeper Account was created successfully
                }
                else{ //checks PWKeeper Common File --> input username is not unique
                    printf("Oopsie. That Username is already taken :((\n");
                }
            }
        }
        if(nChoiceMenu1 == 2){ //LogIn PWKeeper Account{
            if(nOrigin == 1){ //user came from Create New Account
                strcpy(loginUser.username, user.username);
                strcpy(loginUser.password, user.password);
                strcpy(loginUser.filename, user.filename);
                nOrigin2 = 1;
            }

            else{ //user's choice is LogIn
                printf("\nLOGIN ACCOUNT\n");
                printf("Enter username: ");
                scanf("%s", loginUser.username); //asks for username
                printf("Enter password: ");
                scanf("%s", loginUser.password); //asks for pw
                if (isValidLoginCredentials(&loginUser) == 1){
                    do{
                        printf("Enter magic number of your choice (number you were asked to remember): ");
                        scanf("%d", &key); //asks for key from user
                    }while(key <= 0); //checks if input key is not negative
                    key += strlen(loginUser.username); //adds salt to key
                    nOrigin2 = 1;
                }
                else{
                    switch (isValidLoginCredentials(&loginUser)) 
                    {
                        case 0: printf("Oopsie. Username doesn't exist :((\n\n"); break; //invalid login credentials (invalid username input)
                        case 2: printf("Oopsie. Invalid password:((\n"); break; //invalid login credentials (invalid pw input)
                        default: break;
                    }
                }
            }

            if(nOrigin2 == 1){
                displayMainMenu(); //displays Main Menu(displayPW/addPW/changePW/deletePW/changePWKeeperPW/exit)
                changeTextColor(15);
                scanf("%d", &nChoiceMainMenu); //asks for input Main Menu(displayPW/addPW/changePW/deletePW/changePWKeeperPW/exit)
                while(nChoiceMainMenu != 0){ 
                    if(nChoiceMainMenu == 1){ //displays all pw from Personal File
                        printf("\nACCOUNTS OF %s\n\n", loginUser.username);
                        displayAllPWFromPersonalFile(loginUser, key); //displays all pw from Personal File(accountName, username, password)
                    }
                    else if(nChoiceMainMenu == 2){ //adds pw to Personal File
                        printf("\nADD PASSWORD MENU\n\n");
                        printf("Enter new account name: ");
                        scanf("%s", loginUserAddPW.accountName);//asks for input accountName 
                        if(isUniqueAcctName(loginUserAddPW, key, loginUser) == 1){//checks if input accountName is unique --> input accountName is unique
                            printf("Enter username for %s: ", loginUserAddPW.accountName);
                            scanf("%s", loginUserAddPW.username);//asks for input username of input accountName
                            printf("Enter password for %s: ", loginUserAddPW.accountName);
                            scanf("%s", loginUserAddPW.password); //asks for input password of input accountName
                            stringToInt2(&userAddPWCopyInt, loginUserAddPW); //copies contents of  loginUserAddPW (struct personalStr) to *userAddPWCopyInt(struct personalInt)
                            encryptNewPWToPersonalFile(key, userAddPWCopyInt, loginUser);//encrypts new pw(accountName, username, password) to personal file
                        }
                        else{
                            printf("\nOopsie. That Account Name already exists :((\n");//input accountName is not unique --> displays error message
                        }
                    }
                    else if(nChoiceMainMenu == 3){ //changes pw from Personal File
                        printf("\nCHANGE PASSWORD MENU\n\n");
                        printf("Enter Account Name (whose password you want to change): ");
                        scanf("%s", loginUserChangePW.accountName); //asks for input accountName
                        printf("Enter Old Password for %s: ", loginUserChangePW.accountName);
                        scanf("%s", loginUserChangePW.password); //asks for input password (old)
                        if(isValidAcctNameAndPW(loginUserChangePW, key, loginUser) == 1){ //checks if input loginUserChangePW (accountName, password) exists from personal file --> valid
                            printf("Enter New Password for %s: ", loginUserChangePW.accountName);
                            scanf("%s", loginUserChangePWNewPW); //asks for input password (new)
                            changePW(loginUserChangePW, key, loginUser, loginUserChangePWNewPW); //replaces password(old) of input loginUserChangePW (accountName) with password(new)
                            printf("Password for %s successfully changed :)\n", loginUserChangePW.accountName); //changePW() execution was succesful --> displays message
                        }
                        else if(isValidAcctNameAndPW(loginUserChangePW, key, loginUser) == 2){
                            printf("Oopsie. Invalid password :((\n"); //input loginUserChangePW (password) is invalid --> displays error message
                        }
                        else{
                            printf("Oopsie. That Account Name does not exist\n"); //input loginUserChangePW (accountName) is invalid --> displays error message
                        }
                    }
                    else if(nChoiceMainMenu == 4){ //deletes pw from Personal File 
                        printf("\nDELETE PASSWORD MENU\n\n");
                        printf("Enter Account Name you want to delete: ");
                        scanf("%s", loginUserDeletePW.accountName); //asks for input accountName
                        if(isUniqueAcctName(loginUserDeletePW, key, loginUser) == 0){ //checks if loginUserDeletePW (accountName) exists from personal file --> valid
                            deletePW(loginUserDeletePW, key, loginUser); //deletes loginUserDeletePW (accountName(with username and password))  from personal file
                            printf("Account successfully deleted :)\n"); //deletePW() execution was successful --> displays message
                        }
                        else{
                            printf("\nOopsie. That Account Name does not exist :((\n"); //input loginUserDeletePW (accountName) is invalid --> displays error message
                        }
                    }
                    else if(nChoiceMainMenu == 5){ //changes pw of PWKeeper Account
                        printf("\nCHANGE PASSWORD FOR PASSWORD KEEPER MENU\n\n");
                        printf("Re-enter your Current Password for Password Keeper Account: ");
                        scanf("%s", loginUserChangePWKeeperPWOld); //asks for input pw of user's PWKeeper Account (one to be replaced)
                        while(strcmp(loginUser.password, loginUserChangePWKeeperPWOld) != 0){ //checks if input pw (old) is the same with user's PWKeeper Account pw
                            printf("Oopsie. Invalid password :((\n"); //input pw (old) invalid --> displays error message
                            printf("Re-enter your Current Password for Password Keeper Account: ");
                            scanf("%s", loginUserChangePWKeeperPWOld); //asks for input pw of user's PWKeeper Account (one to be replaced)
                        }
                        printf("Enter New Password you want to replace your Current Password with: ");
                        scanf("%s", loginUserChangePWKeeperPWNew); //asks for input pw of user's PWKeeper Account (one to replace the old one with)
                        changePWKeeperPW(loginUser, loginUserChangePWKeeperPWNew); //changes user's PWKeeper Account pw to input pw(new)
                        printf("Password of your Password Keeper Account successfully changed :)\n"); //changePWKeeperPW() execution was successful --> displays message
                    }
                    else{
                        displayErrorInput1(); //Main Menu choice != 1,2,3,4,5, or 0 --> displays "invalid input" error message
                    }
                    displayMainMenu(); //displays Main Menu(displayPW/addPW/changePW/deletePW/changePWKeeperPW/exit)
                    changeTextColor(15);
                    scanf("%d", &nChoiceMainMenu); //asks for input Main Menu(displayPW/addPW/changePW/deletePW/changePWKeeperPW/exit)
                }
                switch (nChoiceMainMenu){ 
                    case 0: system("cls"); break; //Main Menu choice == 0 --> exits PW Keeper Account (Main Menu) --> redirects to PW Keeper Menu
                    default: system("cls"); break;
                }
            }
        }
        else{
            displayErrorInput1(); //PWKeeper Menu Choice != 1, 2, or 0 --> displays "invalid input" error message
        }
        displayMenu1(); //displays PWKeepr Menu (Create New Account/LogIn/Exit)
        changeTextColor(15);
        scanf("%d", &nChoiceMenu1); //input PWKeepr Menu (Create New Account/LogIn/Exit)
        system("cls");
    }
    displayExitMessage(); //displays exit message
    return 0;
}

/*Description: prints text with color
*Parameters: int value of text color
*Return Value: none (text with color)
*/
void changeTextColor(int nColor)
{
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), nColor);
}

/*Description: prints Password Keeper Menu
*Parameters: none
*Return Value: none (displays Password Keeper Menu)
*/
void displayMenu1()
{
    changeTextColor(6);
    printf("  ad8888888888ba\n");
    printf(" dP'         `\"8b,\n");
    printf(" 8  ,aaa,       \"Y888a     ,aaaa,     ,aaa,  ,aa,\n");
    printf(" 8  8' `8           \"88baadP\"\"\"\"YbaaadP\"\"\"YbdP\"\"Yb\n");
    printf(" 8  8   8              \"\"\"        \"\"\"      \"\"    8b\n");
    printf(" 8  8, ,8         ,aaaaaaaaaaaaaaaaaaaaaaaaddddd88P\n");
    printf(" 8  `\"\"\"'       ,d8\"\"   PASSWORD KEEPER MENU\n");
    printf(" Yb,         ,ad8\"      Press[1] Create New Account\n");    
    printf("  \"Y8888888888P\"        Press[2] Login\n");
    printf("                        Press[0] Exit\n");
    printf("Enter choice: ");
}

/*Description: prints Exit Message
*Parameters: none
*Return Value: none (displays Exit Message)
*/
void displayExitMessage()
{
    changeTextColor(2);
    printf("\t\t\t\t\t\t\t\t  *                    *     .--.                                              *\n");
    printf("\t\t\t\t\t\t\t\t     *                      / /  `                      *   *       *          + *   *       *          +\n");
    printf("\t\t\t\t\t\t\t\t  *        +               | |                       *\n");
    printf("\t\t\t\t\t\t\t\t                  '         \\ \\__,                          *   *       *          + *   *       *          +\n");
    printf("\t\t\t\t\t\t\t\t*             *          +   '--'  *    *                 *       *          + *   *       *          +\n");
    printf("\t\t\t\t\t\t\t\t                  +   *                    *                                                         *\n");
    printf("\t\t\t\t\t\t\t\t     +                 *   *       *          +                              *   *       *          +\n");
    printf("\t\t\t\t\t\t\t\t                 c==o\n");
    printf("\t\t\t\t\t\t\t\t *             _/____\\_            +    *              *                                        * *   *       *\n");            
    printf("\t\t\t\t\t\t\t\t        _.,--'\" ||^ || \"`z._            *   *       *                                   +\n");
    printf("\t\t\t\t\t\t\t\t *     /_/^ ___\\||  || _/o\\ \"`-._          +       *       +       *   *       *\n");          
    printf("\t\t\t\t\t\t\t\t     _/  ]. L_| || .||  \\_/_  . _`--._ *   *       *                                    + *   *       *          +\n");
    printf("\t\t\t\t\t\t\t\t    /_~7  _ . \" ||. || /] \\ ]. (_)  . \"`--.     *              + *   *       *          +\n");
    printf("\t\t\t\t\t\t\t\t   |__7~.(_)_ []|+--+|/____T_____________L|\n");
    printf("\t\t\t\t\t\t\t\t   |__|  _^(_) /^   __\\____ _   _|            +                                            *         *     *\n");
    printf("\t\t\t\t\t\t\t\t   |__| (_){_) F ]P{__ L___ _   _]    *   *       *                      + *   *       *          +\n");
    printf("\t\t\t\t\t\t\t\t * |__| . _(_) \\v     /__________|________\n");
    printf("\t\t\t\t\t\t\t\t   l__l_ (_). []|+-+-<\\^   L  . _   - ---L| *   *         *       *          +            * *                +\n");
    printf("\t\t\t\t\t\t\t\t    \\__\\    __. ||^l  \\Y] /_]  (_) .  _,--'\n");
    printf("\t\t\t\t\t\t\t\t  *   \\~_]  L_| || .\\ .\\/~.    _,--'\"  *   *       *          + *   *       *          +\n");
    printf("\t\t\t\t\t\t\t\t       \\_\\ . __/||  |\\  \\`-+-<'\"  *   *       *          +\n");
    printf("\t\t\t\t\t\t\t\t    *    \"`---._|F__P|X o~~|[\\      *   *               *   *       *  *   *       *  *   *       *  *   *       *\n");  
    printf("\t\t\t\t\t\t\t\t *              \\____/ \\___|[//           *           *           *            *         *       *       *\n");    
    printf("\t\t\t\t\t\t\t\t                 `--'   `--+-'           *   *       *           *   *       *           *   *          *  *   *\n");
    printf("\t\t\t\t\t\t\t\t      *       +t              +          o                  *                          m              *o   m\n");
    printf("\t\t\t\t\t\t\t\t                                Thank you for using Password Keeper. See you soon! :)))\n\n");
}

/*Description: prints Error Input
*Parameters: none
*Return Value: none (displays Error Input)
*/
void displayErrorInput1()
{
    printf("Oopsie. Invalid input :(\n");
}

/*Description: prints Main Menu
*Parameters: none
*Return Value: none (displays Main Menu)
*/
void displayMainMenu()
{
    changeTextColor(3);
    printf("\n     ________________________________________________\n");
    printf("    /                                                \\\n");
    printf("   |    _________________________________________     |\n");
    printf("   |   |                                         |    |\n");
    printf("   |   |                                         |    |\n");
    printf("   |   |              MAIN MENU                  |    |\n");
    printf("   |   |     Press[1] Display all passwords      |    |\n");
    printf("   |   |     Press[2] Add a password             |    |\n");
    printf("   |   |     Press[3] Change a password          |    |\n");
    printf("   |   |     Press[4] Delete a password          |    |\n");
    printf("   |   |     Press[5] Change your password       |    |\n");
    printf("   |   |              for Password Keeper        |    |\n");
    printf("   |   |     Press[0] Logout Account             |    |\n");
    printf("   |   |                                         |    |\n");
    printf("   |   |_________________________________________|    |\n");
    printf("   |                                                  |\n");
    printf("   \\_________________________________________________/\n");
    printf("          \\___________________________________/\n");
    printf("   Enter choice: "); 
}

/*Description: decrypts username from COMMONFILE
*Parameters: personInt read, personStr *decrypted, int key, char usernameNewACcount[]
*Return Value: none (decrypted username)
*/
void decryptCheckPWKeeperFileUsername(personInt read, personStr *decrypted, int key, char usernameNewACcount[])
{
    int i, cycle, subtrahend, k, last;
    cycle = key % 10;
    subtrahend = key;
    subtrahend = read.username[0];
    read.username[0] -= key;
    cycle--;
    for(i = 1; read.username[i] != '\0'; i++){
        if(cycle == 0) {
            cycle = key % 10;
            subtrahend = key;
        }
        k = read.username[i];
        read.username[i] -= subtrahend;
        cycle--;
        subtrahend = k;
    }
    for(i = 0; read.username[i] != '\0'; i++){
        (*decrypted).username[i] = read.username[i];
    }
    last = i;
    for(i = last; i < 100; i++) (*decrypted).username[i] = '\0';
    //printf("%s\n", (*decrypted).username);
}

/*Description: decrypts filename from COMMONFILE
*Parameters: personInt read, personStr *decrypted, int key, char filenameNewACcount[]
*Return Value: none (decrypted filename)
*/
void decryptCheckPWKeeperFileFilename(personInt read, personStr *decrypted, int key, char filenameNewACcount[])
{
    int i, cycle, subtrahend, k, last;
    cycle = key % 10;
    subtrahend = key;
    subtrahend = read.filename[0];
    read.filename[0] -= key;
    cycle--;
    for(i = 1; read.filename[i] != '\0'; i++){
        if(cycle == 0) {
            cycle = key % 10;
            subtrahend = key;
        }
        k = read.filename[i];
        read.filename[i] -= subtrahend;
        cycle--;
        subtrahend = k;
    }
    for(i = 0; read.filename[i] != '\0'; i++){
        (*decrypted).filename[i] = read.filename[i];
    }
    last = i;
    for(i = last; i < 100; i++) (*decrypted).filename[i] = '\0';
}

/*Description: checks if username entered during Create New Account is unique
*Parameters: char usernameNewAccount[]
*Return Value: int (0 = usernameNewAccount[] is unique; 1 = usernameNewAccount[] is not unique)
*/
int checkPWKeeperFile(char usernameNewAccount[])
{
    int found = 0, stop = 0, key;
    char newLine;
    personInt read;
    personStr decrypted;
    FILE *ptr;
    key = 18;
    ptr = fopen(COMMONFILE, "rb");
    while(fread(&read, sizeof(read), 1, ptr) == 1){
        decryptCheckPWKeeperFileUsername(read, &decrypted, key, usernameNewAccount);
        if(strcmp(decrypted.username, usernameNewAccount) == 0){
            found = 1;
        }
    }
    fclose(ptr);
    return found;
}

/*Description: checks if filename input during Create New Account is valid
*Parameters: personStr user
*Return Value: int (1 = valid; 0 = invalid(no ".dat"))
*/
int isValidFilenameChecker1(personStr user) 
{
    int i, k, nBin = 0, nDat = 0;
    char dat[4] = ".dat", bin[4] = ".bin", store[4];
    for(i = strlen(user.filename) - 4, k = 0; k <= 4; i++, k++){
        store[k] = user.filename[i];
    }
    store[k] = '\0';
    //printf("%s\n", store);
    if(strcmp(store, dat) == 0) nDat = 1;
    if(strcmp(store, bin) == 0) nBin = 1;
    if(nDat == 1) return 1;
    else return 0;
}

/*Description: checks if filename input during Create New Account is unique
*Parameters: personStr user, int *error
*Return Value: int (1 = filename found in common file, *error = 1; 
0 = filename is unique, *error  = 0)
*/
int isValidFilenameChecker2(personStr user, int *error)
{
    int found = 0, key;
    personInt read;
    personStr decrypted;
    FILE *ptr;
    key = 18;
    ptr = fopen(COMMONFILE, "rb");
    while(fread(&read, sizeof(read), 1, ptr) == 1){
        decryptCheckPWKeeperFileFilename(read, &decrypted, key, user.filename);
        if(strcmp(decrypted.filename, user.filename) == 0){
            found = 1;
            *error = 1;
        }
    }
    fclose(ptr);
    return found;
}

int isValidFilenameChecker3(personStr user, int *error2)
{
    if(strcmp(user.filename, COMMONFILE) == 0){
        *error2 = 1;
        return 0;
    }
    else return 1;
}

/*Description: creates personal file based from user input during Create New Account
*Parameters: personStr user
*Return Value: none (personal file is created)
*/
void createPersonalFile(personStr user)
{
    FILE *ptr;
    ptr = fopen(user.filename, "wb");
    fclose(ptr);
}

/*Description: transfers contents of personStr user to personInt *userCopyInt
*Parameters: personStr user, personInt *userCopyInt
*Return Value: none (userCopyInt initialized with contents)
*/
void stringToInt1(personStr user, personInt *userCopyInt)
{
    int i, last;
    for(i = 0; i < strlen(user.username); i++){
        (*userCopyInt).username[i] = user.username[i];
    }
    (*userCopyInt).username[i] = '\0';
    for(i = 0; i < strlen(user.password); i++){
        (*userCopyInt).password[i] = user.password[i];
    }
    (*userCopyInt).password[i] = '\0';
    for(i = 0; i < strlen(user.filename); i++){
        (*userCopyInt).filename[i] = user.filename[i];
    }
    (*userCopyInt).filename[i] = '\0';
}

/*Description: encrypts New Account to user's personal file
*Parameters: personInt userCopyInt, personStr user
*Return Value: none (encrypted userCopyInt written into user's personal file)
*/
void encryptNewAccountInPWKeeperFile(personInt userCopyInt, personStr user)
{
    int cycle = 1, i, addend, key;
    key = 18;
    addend = key;
    for(i = 0; userCopyInt.username[i] != '\0'; i++){
        if(cycle == key % 10 + 1){
            cycle = 1;
            addend = key;
        }
        userCopyInt.username[i] += addend;
        cycle++;
        addend = userCopyInt.username[i];
    }
    cycle = 1; addend = key;
    for(i = 0; userCopyInt.password[i] != '\0'; i++){
        if(cycle == key % 10 + 1){
            cycle = 1;
            addend = key;
        }
        userCopyInt.password[i] += addend;
        cycle++;
        addend = userCopyInt.password[i];
    }
    cycle = 1; addend = key;
    for(i = 0; userCopyInt.filename[i] != '\0'; i++){
        if(cycle == key % 10 + 1){
            cycle = 1;
            addend = key;
        }
        userCopyInt.filename[i] += addend;
        cycle++;
        addend = userCopyInt.filename[i];
    }
    FILE *ptr;
    ptr = fopen(COMMONFILE, "ab");
    fwrite(&userCopyInt, sizeof(userCopyInt), 1, ptr);
    fclose(ptr);
}

/*Description: decrypts contents of COMMONFILE
*Parameters: personInt encrypted, personStr *decrypted, int key, personStr loginUser
*Return Value: none (decrypted login credentials)
*/
void decryptPWKeeperLogin(personInt encrypted, personStr *decrypted, int key, personStr loginUser)
{
    int i, cycle, subtrahend, k, last;
    cycle = key % 10;
    subtrahend = key;
    subtrahend = encrypted.username[0];
    encrypted.username[0] -= key;
    cycle--;
    for(i = 1; encrypted.username[i] != '\0'; i++){
        if(cycle == 0) {
            cycle = key % 10;
            subtrahend = key;
        }
        k = encrypted.username[i];
        encrypted.username[i] -= subtrahend;
        cycle--;
        subtrahend = k;
    }
    cycle = key % 10;
    subtrahend = key;
    subtrahend = encrypted.password[0];
    encrypted.password[0] -= key;
    cycle--;
    for(i = 1; encrypted.password[i] != '\0'; i++){
        if(cycle == 0) {
            cycle = key % 10;
            subtrahend = key;
        }
        k = encrypted.password[i];
        encrypted.password[i] -= subtrahend;
        cycle--;
        subtrahend = k;
    }
    cycle = key % 10;
    subtrahend = key;
    subtrahend = encrypted.filename[0];
    encrypted.filename[0] -= key;
    cycle--;
    for(i = 1; encrypted.filename[i] != '\0'; i++){
        if(cycle == 0) {
            cycle = key % 10;
            subtrahend = key;
        }
        k = encrypted.filename[i];
        encrypted.filename[i] -= subtrahend;
        cycle--;
        subtrahend = k;
    }
    for(i = 0; encrypted.username[i] != '\0'; i++){
        (*decrypted).username[i] = encrypted.username[i];
    }
    last = i;
    for(i = last; i < 100; i++) (*decrypted).username[i] = '\0';
    for(i = 0; encrypted.password[i] != '\0'; i++){
        (*decrypted).password[i] = encrypted.password[i];
    }
    last = i;
    for(i = last; i < 100; i++) (*decrypted).password[i] = '\0';
    for(i = 0; encrypted.filename[i] != '\0'; i++){
        (*decrypted).filename[i] = encrypted.filename[i];
    }
    last = i;
    for(i = last; i < 100; i++) (*decrypted).filename[i] = '\0';
    /*printf("%s\n", (*decrypted).username);
    printf("%s\n", (*decrypted).password);
    printf("%s\n", (*decrypted).filename);*/
}

/*Description: checks if input login credentials from user can be found in COMMONFILE
*Parameters: personStr *loginUser
*Return Value: int (1 = valid pw and username; 2 = valid username but invalid pw; 
0 = input login credentials does not exist)
*/
int isValidLoginCredentials(personStr *loginUser)
{
    int nFindUsername = 0, nFindPw = 0, i, key;
    personInt encrypted;
    personStr decrypted;
    FILE *ptr;
    ptr = fopen(COMMONFILE, "rb");
    key = 18;
    while (fread(&encrypted, sizeof(encrypted), 1, ptr) == 1){
        decryptPWKeeperLogin(encrypted, &decrypted, key, *loginUser);
        if(strcmp(decrypted.username, (*loginUser).username) == 0){
            nFindUsername = 1;
            if(strcmp(decrypted.password, (*loginUser).password) == 0){
                nFindPw = 1;
                strcpy((*loginUser).filename, decrypted.filename);
            }
        }
    }
    fclose(ptr);
    if(nFindUsername == 1 && nFindPw == 1) return 1;
    else if(nFindUsername == 1 && nFindPw == 0) return 2;
    else return 0;
}

/*Description: decrypts user's personal file
*Parameters: personalStr *decrypted, int key, personalInt user, personalStr loginUserAddPW
*Return Value: none (decrypted Account Name from user's personal file)
*/
void decryptAcctName(personalStr *decrypted, int key, personalInt user, personalStr loginUserAddPW)
{
    int i, cycle, subtrahend, k, last;
    cycle = key % 10;
    subtrahend = key;
    subtrahend = user.accountName[0];
    user.accountName[0] -= key;
    cycle--;
    for(i = 1; user.accountName[i] != '\0'; i++){
        if(cycle == 0) {
            cycle = key % 10;
            subtrahend = key;
        }
        k = user.accountName[i];
        user.accountName[i] -= subtrahend;
        cycle--;
        subtrahend = k;
    }
    for(i = 0; user.accountName[i] != '\0'; i++){
        (*decrypted).accountName[i] = user.accountName[i];
    }
    last = i;
    for(i = last; i < 100; i++) (*decrypted).accountName[i] = '\0';
}

/*Description: checks if input Account Name already exists in user's personal file
*Parameters: personalStr loginUserAddPW, int key, personStr loginUser
*Return Value: int (1 = input Account Name is unique; 0 = input Account Name is not unique)
*/
int isUniqueAcctName(personalStr loginUserAddPW, int key, personStr loginUser)
{
    personalInt user;
    personalStr decrypted;
    int i, found = 0;
    FILE *ptr;
    ptr = fopen(loginUser.filename, "rb");
    while(fread(&user, sizeof(user), 1, ptr) == 1){
        //fread(&user, sizeof(user), 1, ptr);
        decryptAcctName(&decrypted, key, user, loginUserAddPW);
        if(strcmp(decrypted.accountName, loginUserAddPW.accountName) == 0){
            found = 1;
        }
    }
    fclose(ptr);
    if(found == 0) return 1;
    else return 0;
}

/*Description: decrypts contents of user's personal file
*Parameters: personalStr *decrypted, personalInt user, int key
*Return Value: void (decrypted Account Name, username, and pw from user's personal file)
*/
void decryptAllPWFromPersonalFile(personalStr *decrypted, personalInt user, int key)
{
    int i, cycle, subtrahend, k, last;
    cycle = key % 10;
    subtrahend = key;
    subtrahend = user.accountName[0];
    user.accountName[0] -= key;
    cycle--;
    for(i = 1; user.accountName[i] != '\0'; i++){
        if(cycle == 0) {
            cycle = key % 10;
            subtrahend = key;
        }
        k = user.accountName[i];
        user.accountName[i] -= subtrahend;
        cycle--;
        subtrahend = k;
    }
    cycle = key % 10;
    subtrahend = key;
    subtrahend = user.username[0];
    user.username[0] -= key;
    cycle--;
    for(i = 1; user.username[i] != '\0'; i++){
        if(cycle == 0) {
            cycle = key % 10;
            subtrahend = key;
        }
        k = user.username[i];
        user.username[i] -= subtrahend;
        cycle--;
        subtrahend = k;
    }
    cycle = key % 10;
    subtrahend = key;
    subtrahend = user.password[0];
    user.password[0] -= key;
    cycle--;
    for(i = 1; user.password[i] != '\0'; i++){
        if(cycle == 0) {
            cycle = key % 10;
            subtrahend = key;
        }
        k = user.password[i];
        user.password[i] -= subtrahend;
        cycle--;
        subtrahend = k;
    }
    for(i = 0; user.accountName[i] != '\0'; i++){
        (*decrypted).accountName[i] = user.accountName[i];
    }
    last = i;
    for(i = last; i < 100; i++) (*decrypted).accountName[i] = '\0';
    for(i = 0; user.username[i] != '\0'; i++){
        (*decrypted).username[i] = user.username[i];
    }
    last = i;
    for(i = last; i < 100; i++) (*decrypted).username[i] = '\0';
    for(i = 0; user.password[i] != '\0'; i++){
        (*decrypted).password[i] = user.password[i];
    }
    last = i;
    for(i = last; i < 100; i++) (*decrypted).password[i] = '\0';
}

/*Description: displays all of the contents of user's personal file
*Parameters: personStr loginUser, int key
*Return Value: void (displays all of the contents of user's personal file)
*/
void displayAllPWFromPersonalFile(personStr loginUser, int key)
{
    personalInt user;
    personalStr decrypted;
    FILE *ptr;
    int i;
    ptr = fopen(loginUser.filename, "rb");
    while(fread(&user, sizeof(user), 1, ptr) == 1){
        decryptAllPWFromPersonalFile(&decrypted, user, key);
        printf("Account Name: %s\n", decrypted.accountName);
        printf("Username: %s\n", decrypted.username);
        printf("Password: %s\n\n", decrypted.password);
    }
    printf("\n");
    fclose(ptr);
}

/*Description: transfers contents of personalStr user to personalInt *userAddPWCopyInt
*Parameters: personalInt *userAddPWCopyInt, personalStr loginUserAddPW
*Return Value: none (userAddPWCopyInt initialized with contents)
*/
void stringToInt2(personalInt *userAddPWCopyInt, personalStr loginUserAddPW)
{
    int i;
    for(i = 0; i < strlen(loginUserAddPW.accountName); i++){
        (*userAddPWCopyInt).accountName[i] = loginUserAddPW.accountName[i];
    }
    (*userAddPWCopyInt).accountName[i] = '\0';
    for(i = 0; i < strlen(loginUserAddPW.username); i++){
        (*userAddPWCopyInt).username[i] = loginUserAddPW.username[i];
    }
    (*userAddPWCopyInt).username[i] = '\0';
    for(i = 0; i < strlen(loginUserAddPW.password); i++){
        (*userAddPWCopyInt).password[i] = loginUserAddPW.password[i];
    }
    (*userAddPWCopyInt).password[i] = '\0';
}

/*Description: encrypts newly added Account and writes it into user's personal file (mode = "ab")
*Parameters: int key, personalInt userAddPWCopyInt, personStr loginUser
*Return Value: none (encrypted Account written into user's personal file)
*/
void encryptNewPWToPersonalFile(int key, personalInt userAddPWCopyInt, personStr loginUser)
{
    int cycle = 1, i, addend;
    addend = key;
    for(i = 0; userAddPWCopyInt.accountName[i] != '\0'; i++){
        if(cycle == key % 10 + 1){
            cycle = 1;
            addend = key;
        }
        userAddPWCopyInt.accountName[i] += addend;
        cycle++;
        addend = userAddPWCopyInt.accountName[i];
    }
    cycle = 1; addend = key;
    for(i = 0; userAddPWCopyInt.username[i] != '\0'; i++){
        if(cycle == key % 10 + 1){
            cycle = 1;
            addend = key;
        }
        userAddPWCopyInt.username[i] += addend;
        cycle++;
        addend = userAddPWCopyInt.username[i];
    }
    cycle = 1; addend = key;
    for(i = 0; userAddPWCopyInt.password[i] != '\0'; i++){
        if(cycle == key % 10 + 1){
            cycle = 1;
            addend = key;
        }
        userAddPWCopyInt.password[i] += addend;
        cycle++;
        addend = userAddPWCopyInt.password[i];
    }
    FILE *ptr;
    ptr = fopen(loginUser.filename, "ab");
    fwrite(&userAddPWCopyInt, sizeof(userAddPWCopyInt), 1, ptr);
    fclose(ptr);
}

/*Description: checks if input Account Name and Password are in user's personal file
*Parameters: personalStr loginUserChangePW, int key, personStr loginUser
*Return Value: int (1 = input Account Name and Password found; 2 = input Account Name 
found but Password's incorrect; 0 = input Account Name and Password not found)
*/
int isValidAcctNameAndPW(personalStr loginUserChangePW, int key, personStr loginUser)
{
    personalInt user;
    personalStr decrypted;
    int i, foundAcctName = 0, foundPW = 0;
    FILE *ptr;
    ptr = fopen(loginUser.filename, "rb");
    while(!feof(ptr)){
        fread(&user, sizeof(user), 1, ptr);
        decryptAllPWFromPersonalFile(&decrypted, user, key);
        if(strcmp(decrypted.accountName, loginUserChangePW.accountName) == 0){
            foundAcctName = 1;
            if(strcmp(decrypted.password, loginUserChangePW.password) == 0){
                foundPW = 1;
            }
        }
    }
    fclose(ptr);
    if(foundAcctName == 1 && foundPW == 1) return 1;
    else if(foundAcctName == 1 && foundPW == 0) return 2;
    else return 0;
}

/*Description: encrypts newly added Account and writes it into user's personal file (mode = "wb")
*Parameters: int key, personalInt userAddPWCopyInt, personStr loginUser
*Return Value: none (encrypted Account written into user's personal file)
*/
void encryptNewPWToPersonalFileWb(int key, personalInt userAddPWCopyInt, personStr loginUser)
{
    int cycle = 1, i, addend;
    addend = key;
    for(i = 0; userAddPWCopyInt.accountName[i] != '\0'; i++){
        if(cycle == key % 10 + 1){
            cycle = 1;
            addend = key;
        }
        userAddPWCopyInt.accountName[i] += addend;
        cycle++;
        addend = userAddPWCopyInt.accountName[i];
    }
    cycle = 1; addend = key;
    for(i = 0; userAddPWCopyInt.username[i] != '\0'; i++){
        if(cycle == key % 10 + 1){
            cycle = 1;
            addend = key;
        }
        userAddPWCopyInt.username[i] += addend;
        cycle++;
        addend = userAddPWCopyInt.username[i];
    }
    cycle = 1; addend = key;
    for(i = 0; userAddPWCopyInt.password[i] != '\0'; i++){
        if(cycle == key % 10 + 1){
            cycle = 1;
            addend = key;
        }
        userAddPWCopyInt.password[i] += addend;
        cycle++;
        addend = userAddPWCopyInt.password[i];
    }
    FILE *ptr;
    ptr = fopen(loginUser.filename, "wb");
    fwrite(&userAddPWCopyInt, sizeof(userAddPWCopyInt), 1, ptr);
    fclose(ptr);
}

/*Description: changes pw of one of the Accounts from user's personal file
*Parameters: personalStr loginUserChangePW, int key, personStr loginUser, char loginUserChangePWNewPW[]
*Return Value: none (encrypted new pw written into user's personal file)
*/
void changePW(personalStr loginUserChangePW, int key, personStr loginUser, char loginUserChangePWNewPW[])
{
    personalStr decrypted, decryptedAll[100];
    personalInt read, decryptedAllCopyInt;
    int i, decryptedCount = 0;
    FILE *ptr;
    ptr = fopen(loginUser.filename, "rb");
    while(fread(&read, sizeof(read), 1, ptr) == 1){
        decryptAllPWFromPersonalFile(&decrypted, read, key);
        decryptedAll[decryptedCount] = decrypted;
        decryptedCount++;
    }
    fclose(ptr);
    for(i = 0; i < decryptedCount; i++){
        if(strcmp(decryptedAll[i].accountName, loginUserChangePW.accountName) == 0){
            strcpy(decryptedAll[i].password, loginUserChangePWNewPW);
            i = decryptedCount;
        }
    }
    stringToInt2(&decryptedAllCopyInt, decryptedAll[0]);
    encryptNewPWToPersonalFileWb(key, decryptedAllCopyInt, loginUser);
    for(i = 1; i < decryptedCount; i++){
        stringToInt2(&decryptedAllCopyInt, decryptedAll[i]);
        encryptNewPWToPersonalFile(key, decryptedAllCopyInt, loginUser);
    }
}

/*Description: deletes an Account (Account Name, username, password) from user's personal file
*Parameters: personalStr loginUserDeletePW, int key, personStr loginUser
*Return Value: none (deleted an Account from user's personal file)
*/
void deletePW(personalStr loginUserDeletePW, int key, personStr loginUser)
{
    personalStr decrypted, decryptedAll[100];
    personalInt read, decryptedAllCopyInt;
    int i, delete, decryptedCount = 0;
    FILE *ptr;
    ptr = fopen(loginUser.filename, "rb");
    while(fread(&read, sizeof(read), 1, ptr) == 1){
        decryptAllPWFromPersonalFile(&decrypted, read, key);
        decryptedAll[decryptedCount] = decrypted;
        decryptedCount++;
    }
    fclose(ptr);
    for(i = 0; i < decryptedCount; i++){
        if(strcmp(decryptedAll[i].accountName, loginUserDeletePW.accountName) == 0){
            delete = i;
            i = decryptedCount;
        }
    }
    if(delete == decryptedCount - 1){
        decryptedCount--;
    }
    else{
        for(i = delete; i < decryptedCount - 1; i++){
            decryptedAll[i] = decryptedAll[i + 1];
        }
        decryptedCount--;
    }
    if(decryptedCount > 0){
        stringToInt2(&decryptedAllCopyInt, decryptedAll[0]);
        encryptNewPWToPersonalFileWb(key, decryptedAllCopyInt, loginUser);
        for(i = 1; i < decryptedCount; i++){
            stringToInt2(&decryptedAllCopyInt, decryptedAll[i]);
            encryptNewPWToPersonalFile(key, decryptedAllCopyInt, loginUser);
        }
    }
    else{
        ptr = fopen(loginUser.filename, "wb");
        fclose(ptr);
    }
}

/*Description: changes user's Password for their Password Keeper Account
*Parameters: personStr loginUser, char loginUserChangePWKeeperPWNew[]
*Return Value: none (user's Password for their Password Keeper Account changed)
*/
void changePWKeeperPW(personStr loginUser, char loginUserChangePWKeeperPWNew[])
{
    personInt read[100];
    personStr decrypted;
    int readCount = 0, key, i, store, loginUserChangePWKeeperPWNewCopyInt[100], cycle = 1, addend, last;
    FILE *ptr;
    key = 18;
    addend = key;
    ptr = fopen(COMMONFILE, "rb");
    while(fread(&read[readCount], sizeof(read[readCount]), 1, ptr) == 1){
        decryptPWKeeperLogin(read[readCount], &decrypted, key, loginUser);
        if(strcmp(decrypted.username, loginUser.username) == 0) store = readCount;
        readCount++;    
    }
    fclose(ptr);
    for(i = 0; loginUserChangePWKeeperPWNew[i] != '\0'; i++) loginUserChangePWKeeperPWNewCopyInt[i] = loginUserChangePWKeeperPWNew[i];
    loginUserChangePWKeeperPWNewCopyInt[i] = '\0';
    for(i = 0; loginUserChangePWKeeperPWNewCopyInt[i] != '\0'; i++){
        if(cycle == key % 10 + 1){
            cycle = 1;
            addend = key;
        }
        loginUserChangePWKeeperPWNewCopyInt[i] += addend;
        cycle++;
        addend = loginUserChangePWKeeperPWNewCopyInt[i];
    }
    for(i = 0; loginUserChangePWKeeperPWNewCopyInt[i] != '\0'; i++) read[store].password[i] = loginUserChangePWKeeperPWNewCopyInt[i];
    last = i;
    for(i = last; i < 100; i++) read[store].password[i] = '\0';

    ptr = fopen(COMMONFILE, "wb");
    fwrite(&read[0], sizeof(read[0]), 1, ptr);
    fclose(ptr);

    ptr = fopen(COMMONFILE, "ab");
    for(i = 1; i < readCount; i++) fwrite(&read[i], sizeof(read[i]), 1, ptr);
    fclose(ptr);
}