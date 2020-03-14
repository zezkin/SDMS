#include <iostream>
#include <cstdlib>
#include <fstream>



#define cmdwidth 120

using namespace std;

int line_num = 0;

//calc line data in data folder.
void calc_lines();


//Displaying menu screen.
void menuscreen();

//Cout text given in "mode.
void TIM (string text, char mode, int endline);

//Recording data
void record_data();

//Modify data
void modify_data();

//Listing existing data.
void list_data();

//Erasing all data.
void delete_data();

int main()
{
    //Setting window dimensions.
    //system("MODE CON COLS=100 LINES=20");
    menuscreen();



}

//Cout text given in "mode".
void TIM (string text, char mode, int endline = 1)
{
    int len = text.size(), beg = 0;
    switch(mode)
    {
        //To show text in the middle.
        case 'm':
            //begin column.
            beg = (cmdwidth - len) / 2;
            for(int i =0; i < cmdwidth - len; i++)
            {
                if (i == beg)
                    cout << text;
                else
                    cout << " ";
            }
            if (endline == 1)
                cout << endl;
            break;

        //Begining of a paragraoh.
        case 'f':
            //begin column.
            beg = cmdwidth / 3;
            for(int i =0; i < cmdwidth - len; i++)
            {
                if (i == beg)
                {
                    cout << text;
                    if (endline == 0)
                        break;
                }

                else
                    cout << " ";
            }
            if (endline == 1)
                cout << endl;
            break;

    }
}

//Displays menuscreen.
void menuscreen()
{
    calc_lines();
    long long choice;
    do
    {
        system("CLS");
        TIM("===== STUDENT DATABASE MANAGMENT SYSTEM =====", 'm');
        TIM("1- Enter new data.", 'f');
        TIM("2- Modify your existing data.", 'f');
        TIM("3- Listing existing data.", 'f');
        TIM("4- Delete existing data.", 'f');
        TIM("5- Exit program.", 'f');
        TIM("Select your choice :=> ", 'f', 0);
        cin >> choice;
    }
    while(choice < 1 || choice > 5);
    switch(choice)
    {
    case 1:
        system("CLS");
        record_data();
        break;
    case 2:
        system("CLS");
        modify_data();
        break;
    case 3:
        system("CLS");
        list_data();
        break;
    case 4:
        system("CLS");
        delete_data();
        break;
    case 5:
        return;

    }
}
//Recording data
void record_data()
{
    string ch;
    string data;
    fstream record;
    //Opening file.
    record.open("records.txt", ios::app);
    if (!record.is_open())
    {
        cout << "Cannot open the file! \a";
        return;
    }
    //Entering data.
    do
    {
        cout << "First name: ";
        cin >> data;
        record << data << " ";

        cout << "Last name: ";
        cin >> data;
        record << data << " ";
        cout << "Section number: ";
        cin >> data;
        record << data << " ";
        cout << "Favorite subject: ";
        cin >> data;
        record << data << " ";
        record << endl;
        do
        {
            cout << "Another record (Y/N)? ";
            cin >> ch;
        }
        while (ch[0] != 'y' & ch[0] != 'Y' & ch[0] != 'n' & ch[0] != 'N');
        system("CLS");

    }
    while (ch[0] == 'y' || ch[0] == 'Y');
    record.close();
    menuscreen();



}

//Modify data
void modify_data()
{
    int num = 0;
    string line;
    do
    {
        cout << "Enter which number to modify (i.e #..) : ";
        cin >> num;
    }
    while(num < 1 || num > line_num);

    fstream record;
    record.open("records.txt", ios::in);
    //Checking validity of the file.
    if (!record.is_open())
    {
        cout << "Cannot open the file! \a";
        return;
    }
    //Reaching specific line
    if ( num != 1)
    {
        for (int i = 0 ; i < num - 1 ; i++)
        {
            getline(record, line);
        }
    }

    getline(record, line);
    // SHOWING THE MODFIY LINE IN THE FORMAT.
        cout << num << "- " << endl;
        int j = 0;
        cout << "   First name: ";
        while (line[j] != ' ')
        {
            cout << line[j];
            j++;
        }
        j++;
        cout << endl;
        cout << "   Last name: ";
        while (line[j] != ' ')
        {
            cout << line[j];
            j++;
        }
        j++;
        cout << endl;
        cout << "   Section: ";
        while (line[j] != ' ')
        {
            cout << line[j];
            j++;
        }
        j++;
        cout << endl;
        cout << "   Favorite subject: ";
        while (line[j] != ' ')
        {
            cout << line[j];
            j++;
        }
        cout << endl;
    ///////////////////////////////////
    //CREATING TEMP FILE TO MODIFY.
    record.close();
    system("PAUSE");
    system("CLS");
    //Modifying piece
    fstream infile, tmpfile;
    string tmpline;
    infile.open("records.txt", ios::in);
    tmpfile.open("temprecords.txt", ios::out);
    int i = 0;
    while(true)
    {
        i++;
        getline(infile, tmpline);
        if (infile.eof())                      // check for EOF
            break;

        if (i == num)
        {

            string data;
            cout << "First name: ";
            cin >> data;
            tmpfile << data << " ";

            cout << "Last name: ";
            cin >> data;
            tmpfile << data << " ";
            cout << "Section number: ";
            cin >> data;
            tmpfile << data << " ";
            cout << "Favorite subject: ";
            cin >> data;
            tmpfile << data << " ";
            tmpfile << endl;
        }
        else
        {
            tmpfile << tmpline << endl;
        }

    }
    infile.close();
    tmpfile.close();
    //Copying tmpfile text into the original.
    infile.open("records.txt", ios::out);
    tmpfile.open("temprecords.txt", ios::in);
    i = 0;
    while(true)
    {
        i++;
        getline(tmpfile, tmpline);
        if (tmpfile.eof())                      // check for EOF
            break;
        infile << tmpline;
        infile << endl;

    }



    infile.close();
    tmpfile.close();
    remove("temprecords.txt");

    system("PAUSE");
    menuscreen();
}

//Listing existing data.
void list_data()
{
    fstream record;
    string line;
    record.open("records.txt", ios::in);

    if (!record.is_open())
    {
        cout << "Cannot open the file! \a";
        return;
    }
    int i = 1;
    int j;
    while(true)
    {
        getline(record, line);
        if (record.eof())                      // check for EOF
            break;
        cout << i << "- " << endl;
        j = 0;
        cout << "   First name: ";
        while (line[j] != ' ')
        {
            cout << line[j];
            j++;
        }
        j++;
        cout << endl;
        cout << "   Last name: ";
        while (line[j] != ' ')
        {
            cout << line[j];
            j++;
        }
        j++;
        cout << endl;
        cout << "   Section: ";
        while (line[j] != ' ')
        {
            cout << line[j];
            j++;
        }
        j++;
        cout << endl;
        cout << "   Favorite subject: ";
        while (line[j] != ' ')
        {
            cout << line[j];
            j++;
        }
        cout << endl;
        i++;
    }
    record.close();
    system("PAUSE");
    menuscreen();

}
//Erasing all data.
void delete_data()
{
    fstream record;
    record.open("records.txt", ios::out);
    cout << "Deleting data..." << endl;
    if (!record.is_open())
    {
        cout << "Cannot open the file! \a";
        return;
    }
    cout << "Data has been sucessfully deleted." << endl;
    system("PAUSE");
    record.close();
    menuscreen();
}

//calc line data in data folder.
void calc_lines()
{
    line_num = 0;
    fstream record;
    record.open("records.txt", ios::in);
    if (!record.is_open())
    {
        cout << "Cannot open the file! \a";
        return;
    }
    string temp;
    while(true)
    {

        getline(record, temp );
        if (record.eof())                      // check for EOF
            break;
        line_num ++;
    }

    record.close();

}

