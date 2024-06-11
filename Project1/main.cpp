#include <bits/stdc++.h>

#include <Windows.h>

#include <stdlib.h>

#include <chrono>

#include <ctime>

#include "mysql_connection.h"

#include <cppconn/driver.h>

#include <cppconn/exception.h>

#include <cppconn/prepared_statement.h>

#include <cppconn/resultset.h>


using namespace std;

sql::Connection* connect() {
    sql::Driver* driver;
    sql::Connection* con;
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "ALalmmn1@");
    /* Connect to the MySQL test database */
    con->setSchema("hospital_system");
    return con;
}
struct Address {
    string street1;
    string POBOX;
    string Building_Number;

};
struct Contact {

    string phone;
    string relative_phone;
    string email;

};
struct NewFile {

    string id; //   ------> Main Input

    string first_name;
    string last_name;
    string gender;
    string nationality;
    string blood_group;
    string birthday;
    string age;

    Address address;
    Contact contact;

};

class hospital {

public:

    /*
     *************
     *Prototypies*
     *************
     */

    void create_file() {
        NewFile temp;

        cout << "\n\n\t\t\t\t\t\t" << "  Open a new file\n";
        cout << "\t\t\t\t\t_____________________________________";
        cout << "\n\n\t\t\t\t\tWhat's Your Forename: ";
        cin >> temp.first_name;
        cin.ignore();
        cout << "\n\n\t\t\t\t\tWhat's Your Last Name: ";
        cin >> temp.last_name;
        cin.ignore();
        cout << "\n\n\t\t\t\t\tWhat's Your ID Card: ";
        cin >> temp.id;
        cin.ignore();
        cout << "\n\n\t\t\t\t\tWhat's Your age : ";
        cin >> temp.age;
        cin.ignore();
        cout << "\n\n\t\t\t\t\tWhat's Your Gender: ";
        cin >> temp.gender;
        cin.ignore();
        cout << "\n\n\t\t\t\t\tWhat's Your Nationality: ";
        cin >> temp.nationality;
        cin.ignore();
        cout << "\n\n\t\t\t\t\tWhat's Your Blood Group: ";
        cin >> temp.blood_group;
        cin.ignore();
        cout << "\n\n\t\t\t\t\tWhat's Your Date Of Birth: ";
        cin >> temp.birthday;
        cin.ignore();
        system("cls");

        cout << "\n\n\t\t\t\t\tWhat's Your Phone Number: ";
        cin >> temp.contact.phone;
        cin.ignore();
        cout << "\n\n\t\t\t\t\tWhat's Your E-Mail Address: ";
        cin >> temp.contact.email;
        cin.ignore();
        cout << "\n\n\t\t\t\t\tEnter A Relative's Phone Number: ";
        cin >> temp.contact.relative_phone;

        cout << "\n\n\t\t\t\t\tEnter Your House's Street: ";
        getline(cin, temp.address.street1);
        cin.clear();
        cin.ignore(256, '\n');
        cout << "\n\n\t\t\t\t\tEnter Your Building Number: ";
        cin >> temp.address.Building_Number;
        cin.ignore();
        cout << "\n\n\t\t\t\t\tEnter Your POBox: ";
        cin >> temp.address.POBOX;


        try {
            sql::Connection* con = connect();
            sql::PreparedStatement* pstmt;
            pstmt = con->prepareStatement("INSERT INTO `personinfo`(`ID`,`Forename`,`Last_Name`,`Gender`,`Nationality`,`blood_group`,`Birthday`,`Age`,`Street1`,`POBOX`,`Building_Number`,`Phone`,`relative_phone`,`Email`)VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?);");
            pstmt->setString(1, temp.id);
            pstmt->setString(2, temp.first_name);
            pstmt->setString(3, temp.last_name);
            pstmt->setString(4, temp.gender);
            pstmt->setString(5, temp.nationality);
            pstmt->setString(6, temp.blood_group);
            pstmt->setString(7, temp.birthday);
            pstmt->setString(8, temp.age);
            pstmt->setString(9, temp.address.street1);
            pstmt->setString(10, temp.address.POBOX);
            pstmt->setString(11, temp.address.Building_Number);
            pstmt->setString(12, temp.contact.phone);
            pstmt->setString(13, temp.contact.relative_phone);
            pstmt->setString(14, temp.contact.email);
            pstmt->executeUpdate();
            delete pstmt;
            delete con;
           
        }
        catch (sql::SQLException& e) {
           
            cout << e.getSQLStateCStr();
            cout << "Connection faild";
        }

    };
    void update_file() {
        string ID;
        int Choice;
        NewFile temp;

        startingAgain:
        cout << "\n\n\n\n\t\t\t\t\t\tEnter Your ID: ";
        cin >> ID;
        try {
            sql::Connection* con = connect();
            sql::ResultSet* resultset;
            sql::ResultSetMetaData* MetaData;
            string qruey = "SELECT * FROM personinfo WHERE id  = ?";
            sql::PreparedStatement* pstmt;
            pstmt = con->prepareStatement(qruey);
            pstmt->setString(1, ID);
            resultset = pstmt->executeQuery();
            if (!resultset->next()) {
                cout << "There is no ID matching the entered ID";
                Sleep(2000);
                system("cls");
                //TODO Options
                goto startingAgain;
            }


            Sleep(5000);

        }
        catch (sql::SQLException l) {
            cout << "Somthing unexpeted happend Pls wait for a while for the program to reset";
            Sleep(2000);
            system("cls");
            goto startingAgain;
            
        }
        



        do {

        label: system("cls");

            cout << "\n\n\n\t\t\t\t\t\t\t" << "Update a new file\n";
            cout << "\n\n\t\t\t\tSelect an option:\n";
            cout << "\t\t\t\t__________________________________________________________________________\n\n\n";
            cout << "\t\t\t\t(1) -> Edit Your Forename.\t\t\t(2) -> Edit Your Last Name.\n";
            cout << "\t\t\t\t(3) -> What's Your ID Card.\t\t\t(4) -> Edit Your Age.\n";
            cout << "\t\t\t\t(5) -> Edit Your Gender.\t\t\t(6) -> Edit Your Nationality.\n";
            cout << "\t\t\t\t(7) -> Edit Your Blood Group.\t\t\t(8) -> Edit Your Date Of Birth.\n";
            cout << "\t\t\t\t(9) -> Edit Your Phone Number.\t\t\t(10) -> Edit Your E-Mail Address.\n";
            cout << "\t\t\t\t(11) -> Edit Your Relative's Number.\t\t(12) -> Edit Your House's Street.\n";
            cout << "\t\t\t\t(13) -> Edit Your Building Number.\t\t(14) -> Enter Your POBox.\n\n";
            cout << "\t\t\t\t\t\t\t\t(15) -> Exit\n";
            cout << "\t\t\t\t__________________________________________________________________________\n";
            cout << "\t\t\t\tYour choice? : ";
            cin >> Choice;
            if (!cin.good()) {
                cin.clear();
                cin.ignore(256, '\n');
                system("cls");

                cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter a Valid Number! ";
                Sleep(4000);
                goto label;
            }

            switch (Choice) {
            case 1:

                cout << "\n\n\t\t\t\t\tWhat's Your Forename: ";
                cin >> temp.first_name;
                cin.ignore();
                break;
            case 2:
                cout << "\n\n\t\t\t\t\tWhat's Your Last Name: ";
                cin >> temp.last_name;
                cin.ignore();
                break;
            case 3:
                cout << "\n\n\t\t\t\t\tWhat's Your ID Card: ";
                cin >> temp.id;
                cin.ignore();
                break;
            case 4:
                cout << "\n\n\t\t\t\t\tWhat's Your age : ";
                cin >> temp.age;
                cin.ignore();
                break;
            case 5:
                cout << "\n\n\t\t\t\t\tWhat's Your Gender: ";
                cin >> temp.gender;
                cin.ignore();
                break;
            case 6:
                cout << "\n\n\t\t\t\t\tWhat's Your Nationality: ";
                cin >> temp.nationality;
                cin.ignore();
                break;
            case 7:
                cout << "\n\n\t\t\t\t\tWhat's Your Blood Group: ";
                cin >> temp.blood_group;
                cin.ignore();
                break;
            case 8:
                cout << "\n\n\t\t\t\t\tWhat's Your Date Of Birth: ";
                cin >> temp.birthday;
                cin.ignore();
                break;
            case 9:
                cout << "\n\n\t\t\t\t\tWhat's Your Phone Number: ";
                cin >> temp.contact.phone;
                cin.ignore();
                break;
            case 10:
                cout << "\n\n\t\t\t\t\tWhat's Your E-Mail Address: ";
                cin >> temp.contact.email;
                cin.ignore();
                break;
            case 11:
                cout << "\n\n\t\t\t\t\tEnter A Relative's Phone Number: ";
                cin >> temp.contact.relative_phone;
                cin.ignore();
                break;
            case 12:
                cout << "\n\n\t\t\t\t\tEnter Your House's Street: ";
                getline(cin, temp.address.street1);
                cin.ignore();
                break;
            case 13:
                cout << "\n\n\t\t\t\t\tEnter Your Building Number: ";
                cin >> temp.address.Building_Number;
                cin.ignore();
                break;
            case 14:
                cout << "\n\n\t\t\t\t\tEnter Your POBox: ";
                cin >> temp.address.POBOX;
                break;
            case 15:
                break;
            default:
                system("cls");

                cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter a Valid Number! ";
                Sleep(4000);
                break;
            }
            system("cls");


        } while (Choice != 15);
    };
    void delete_file() {

        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t" << "Delete A File.\n";
        cout << "\t\t\t\t______________________________________________________________\n\n\n";
        string ID;
        cout << "\t\t\t\t\tEnter Your ID: ";
        cin >> ID;


        try {
            sql::Connection* con = connect();
            sql::PreparedStatement* pstmt;

            pstmt = con->prepareStatement("delete from  personinfo where ID = ?");

            pstmt->setString(1,ID);
            pstmt->executeUpdate();
            delete pstmt;
            delete con;
        }
        catch (sql::SQLException& e) {

            cout << "Connection faild";
        }
    };

    void appointment_management() {
        int ID;
        int Choice;
    label_:
        system("cls");
        cout << "\n\n\n\n\t\t\t\t\t\tEnter Your ID: ";
        cin >> ID;
        if (!cin.good()) {
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter a Valid Number! ";
            Sleep(4000);
            goto label_;
        }
        cin.clear();
        cin.ignore(256, '\n');
    label_appointment:
        system("cls");
        cout << "\n\n\n\n\n\t\t\t\t\t\t\t\t" << "Choose An Operation.\n";
        cout << "\t\t\t\t\t\t___________________________________________________\n\n";
        cout << "\t\t\t\t\t\t(1) -> Book An Appoinment.\n\n";
        cout << "\t\t\t\t\t\t(2) -> Update An Appointment.\n\n";
        cout << "\t\t\t\t\t\t(3) -> Delete An Appointment.\n\n";
        cout << "\t\t\t\t\t\t___________________________________________________\n";
        cout << "\t\t\t\t\t\tYour choice? : ";
        cin >> Choice;
        if (!cin.good()) {
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter a Valid Number! ";
            Sleep(4000);
            goto label_appointment;
        }
        system("cls");
        switch (Choice) {
        case 1:
            appointment();
            break;
        case 2:
            update_appointment();
            break;
        case 3:
            delete_appointment();
            break;
        }

    }
    void appointment() {

        cout << "\n\n\t\t\t\t\t\t\t\t" << "Book An Appointment.\n";
        cout << "\t\t\t\t\t\t___________________________________________________";
        int ID;
        cout << "\n\n\n\t\t\t\t\t\tEnter Your ID: ";
        cin >> ID;
        int Choice;
        cin.clear();
        cin.ignore(256, '\n');
    label_appointment:
        system("cls");

        cout << "\n\n\n\t\t\t\t\t\t\tWelcome       \n"; // PUT THE NAME HERE """Forename"""
        cout << "\n\n\t\t\t\t\t\tChoose a health clinic please.\n";
        cout << "\t\t\t\t\t\t______________________________________________";
        cout << "\n\n\n\t\t\t\t\t\t(1) -> Emergency Clinic.\n\n";
        cout << "\t\t\t\t\t\t(2) -> Eye Clinic.\n\n";
        cout << "\t\t\t\t\t\t(3) -> Internal Medicine Clinic.\n\n";
        cout << "\t\t\t\t\t\t(4) -> Dental Clinic.\n\n";
        cout << "\t\t\t\t\t\t(5) -> Psychology Clinic.\n\n";
        cout << "\t\t\t\t\t\t(6) -> Pediatric Clinic.\n\n";
        cout << "\t\t\t\t\t\t(7) -> Heart Clinic.\n\n";
        cout << "\t\t\t\t\t\t(8) -> Surgery Clinic.\n\n";
        cout << "\t\t\t\t\t\t______________________________________________\n\n";
        cout << "\t\t\t\t\t\tYour choice? : ";
        cin >> Choice;
        if (!cin.good()) {
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter a Valid Number! ";
            Sleep(4000);
            goto label_appointment;
        }

        switch (Choice) {
        case 1:
            emergency_section();
            break;
        case 2:
            eye_section();
            break;
        case 3:
            medical_section();
            break;
        case 4:
            dental_section();
            break;
        case 5:
            psychology_section();
            break;
        case 6:
            pediatric_section();
            break;
        case 7:
            heart_section();
            break;
        case 8:
            surgery_section();
            break;
        default:
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter a Valid Number! ";
            Sleep(4000);
            goto label_appointment;
        }

    };
    void delete_appointment() {
    label: system("cls");
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t" << "Delete An Appointment.\n";
        cout << "\t\t\t\t______________________________________________________________\n\n\n";
        string ID;
        cout << "\t\t\t\t\tEnter Your ID: ";
        cin >> ID;
        if (!cin.good()) {
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter a Valid Number! ";
            Sleep(4000);
            goto label;
        }
        system("cls");


        try {
            sql::Connection* con = connect();
            sql::PreparedStatement* pstmt;


            pstmt = con->prepareStatement("update from  personinfo Set Patient_DrID  = NULL, Set Appointment_Day  = NULL, Set Appointment_Hour  = NULL where ID = ?");

            pstmt->setString(1, ID);
            pstmt->executeUpdate();
            delete pstmt;
            delete con;
        }
        catch (sql::SQLException& e) {

            cout << "Connection faild";
        }
    }
    void update_appointment() {
    label: cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t" << "Update An Appointment.\n";
        cout << "\t\t\t\t______________________________________________________________\n\n\n";
        int ID;
        cout << "\t\t\t\t\tEnter Your ID: ";
        cin >> ID;
        if (!cin.good()) {
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter a Valid Number! ";
            Sleep(4000);
            goto label;
        }
        system("cls");
        appointment();
    }

    void emergency_section() {};
    void eye_section() {
        int Choice;
        string Dr;
        string Day;
        string Time;
    label:
        system("cls");

        cout << "\n\n\n\t\t\t\t\t\t\t**Eye Section**\n";
        cout << "\n\n\t\t\t\t\t\tChoose A Doctor Please.\n";
        cout << "\t\t\t\t\t\t______________________________________________";
        cout << "\n\n\n\t\t\t\t\t\t(1) ~ Dr.Ali Ibrahim      ---> Ophthalmology Consultant.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(2) ~ Dr.Rahaf Yousef     ---> Optometrist.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(3) ~ Dr.Mohsen Al-Yousef ---> Retinal Consultant.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(4) ~ Dr.Khaled Ahmed     ---> Refractive Surgery Consultant.\n\n";
        cout << "\t\t\t\t\t\t______________________________________________\n\n";
        cout << "\t\t\t\t\t\tYour choice? : ";
        cin >> Choice;
        if (!cin.good() || Choice > 4 || Choice < 1) {
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter a Valid Number! ";
            Sleep(4000);
            goto label;
        }
        switch (Choice) {
        case 1:
            Dr = "Dr.Ali Ibrahim";
            Day = weekdays();
            Time = hours();
            break;
        case 2:
            Dr = "Dr.Rahaf Yousef";
            Day = weekdays();
            Time = hours();
            break;
        case 3:
            Dr = "Dr.Mohsen Al-Yousef";
            Day = weekdays();
            Time = hours();
            break;
        case 4:
            Dr = "Dr.Khaled Ahmed";
            Day = weekdays();
            Time = hours();
            break;
        };
    };
    void medical_section() {
        int Choice;
        string Dr;
        string Day;
        string Time;
    label:
        system("cls");

        cout << "\n\n\n\t\t\t\t\t\t\t**Medical Section**\n";
        cout << "\n\n\t\t\t\t\t\tChoose A Doctor Please.\n";
        cout << "\t\t\t\t\t\t______________________________________________";
        cout << "\n\n\n\t\t\t\t\t\t(1) ~ Dr.Abdulrahman Badeep ---> Ophthalmology Consultant.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(2) ~ Dr.Salem Ali          ---> Optometrist.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(3) ~ Dr.Fatemah Saleh      ---> Retinal Consultant.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(4) ~ Dr.Norah Saad         ---> Refractive Surgery Consultant.\n\n";
        cout << "\t\t\t\t\t\t______________________________________________\n\n";
        cout << "\t\t\t\t\t\tYour choice? : ";
        cin >> Choice;
        if (!cin.good() || Choice > 4 || Choice < 1) {
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter a Valid Number! ";
            Sleep(4000);
            goto label;
        }
        switch (Choice) {
        case 1:
            Dr = "Dr.Abdulrahman Badeep";
            Day = weekdays();
            Time = hours();
            break;
        case 2:
            Dr = "Dr.Salem Ali";
            Day = weekdays();
            Time = hours();
            break;
        case 3:
            Dr = "Dr.Fatemah Saleh";
            Day = weekdays();
            Time = hours();
            break;
        case 4:
            Dr = "Dr.Norah Saad";
            Day = weekdays();
            Time = hours();
            break;
        }
    };
    void dental_section() {
        int Choice;
        string Dr;
        string Day;
        string Time;
    label:
        system("cls");

        cout << "\n\n\n\t\t\t\t\t\t\t**Dental Section**\n";
        cout << "\n\n\t\t\t\t\t\tChoose A Doctor Please.\n";
        cout << "\t\t\t\t\t\t______________________________________________";
        cout << "\n\n\n\t\t\t\t\t\t(1) ~ Dr.Osamah Karim    ---> Ophthalmology Consultant.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(2) ~ Dr.Basel Ahmed     ---> Optometrist.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(3) ~ Dr.Mohammed Assad  ---> Retinal Consultant.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(4) ~ Dr.Hamzah Eyad     ---> Refractive Surgery Consultant.\n\n";
        cout << "\t\t\t\t\t\t______________________________________________\n\n";
        cout << "\t\t\t\t\t\tYour choice? : ";
        cin >> Choice;
        if (!cin.good() || Choice > 4 || Choice < 1) {
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter a Valid Number! ";
            Sleep(4000);
            goto label;
        }
        switch (Choice) {
        case 1:
            Dr = "Dr.Osamah Karim";
            Day = weekdays();
            Time = hours();
            break;
        case 2:
            Dr = "Dr.Basel Ahmed";
            Day = weekdays();
            Time = hours();
            break;
        case 3:
            Dr = "Dr.Mohammed Assad";
            Day = weekdays();
            Time = hours();
            break;
        case 4:
            Dr = "Dr.Hamzah Eyad";
            Day = weekdays();
            Time = hours();
            break;
        }
    };
    void psychology_section() {
        int Choice;
        string Dr;
        string Day;
        string Time;
    label:
        system("cls");

        cout << "\n\n\n\t\t\t\t\t\t\t**Psychology Section**\n";
        cout << "\n\n\t\t\t\t\t\tChoose A Doctor Please.\n";
        cout << "\t\t\t\t\t\t______________________________________________";
        cout << "\n\n\n\t\t\t\t\t\t(1) ~ Dr.Mohammed Abobaker ---> Ophthalmology Consultant.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(2) ~ Dr.Mohammed Alawi    ---> Optometrist.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(3) ~ Dr.Mohsen Al-Yousef  ---> Retinal Consultant.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(4) ~ Dr.Khaled Abbad      ---> Refractive Surgery Consultant.\n\n";
        cout << "\t\t\t\t\t\t______________________________________________\n\n";
        cout << "\t\t\t\t\t\tYour choice? : ";
        cin >> Choice;
        if (!cin.good() || Choice > 4 || Choice < 1) {
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter a Valid Number! ";
            Sleep(4000);
            goto label;
        }
        switch (Choice) {
        case 1:
            Dr = "Dr.Mohammed Abobaker";
            Day = weekdays();
            Time = hours();
            break;
        case 2:
            Dr = "Dr.Mohammed Alawi";
            Day = weekdays();
            Time = hours();
            break;
        case 3:
            Dr = "Dr.Mohsen Al-Yousef";
            Day = weekdays();
            Time = hours();
            break;
        case 4:
            Dr = "Dr.Khaled Abbad";
            Day = weekdays();
            Time = hours();
            break;
        }
    };
    void pediatric_section() {
        int Choice;
        string Dr;
        string Day;
        string Time;
    label:
        system("cls");

        cout << "\n\n\n\t\t\t\t\t\t\t**Pediatric Section**\n";
        cout << "\n\n\t\t\t\t\t\tChoose A Doctor Please.\n";
        cout << "\t\t\t\t\t\t______________________________________________";
        cout << "\n\n\n\t\t\t\t\t\t(1) ~ Dr.Ahmed Jaber     ---> Ophthalmology Consultant.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(2) ~ Dr.Rayan Al-Ali    ---> Optometrist.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(3) ~ Dr.Saad Taheer     ---> Retinal Consultant.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(4) ~ Dr.Mohammed Ahmed  ---> Refractive Surgery Consultant.\n\n";
        cout << "\t\t\t\t\t\t______________________________________________\n\n";
        cout << "\t\t\t\t\t\tYour choice? : ";
        cin >> Choice;
        if (!cin.good() || Choice > 4 || Choice < 1) {
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter a Valid Number! ";
            Sleep(4000);
            goto label;
        }
        switch (Choice) {
        case 1:
            Dr = "Dr.Ahmed Jaber";
            Day = weekdays();
            Time = hours();
            break;
        case 2:
            Dr = "Dr.Rayan Al-Ali";
            Day = weekdays();
            Time = hours();
            break;
        case 3:
            Dr = "Dr.Saad Taheer";
            Day = weekdays();
            Time = hours();
            break;
        case 4:
            Dr = "Dr.Mohammed Ahmed";
            Day = weekdays();
            Time = hours();
            break;
        }
    };
    void heart_section() {
        int Choice;
        string Dr;
        string Day;
        string Time;
    label:
        system("cls");

        cout << "\n\n\n\t\t\t\t\t\t\t**Heart Section**\n";
        cout << "\n\n\t\t\t\t\t\tChoose A Doctor Please.\n";
        cout << "\t\t\t\t\t\t______________________________________________";
        cout << "\n\n\n\t\t\t\t\t\t(1) ~ Dr.Ibrahim Eyad    ---> Ophthalmology Consultant.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(2) ~ Dr.Fawaz Saleh     ---> Optometrist.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(3) ~ Dr.Bassem Al-Saadi ---> Retinal Consultant.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(4) ~ Dr.Anas Ali        ---> Refractive Surgery Consultant.\n\n";
        cout << "\t\t\t\t\t\t______________________________________________\n\n";
        cout << "\t\t\t\t\t\tYour choice? : ";
        cin >> Choice;
        if (!cin.good() || Choice > 4 || Choice < 1) {
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter a Valid Number! ";
            Sleep(4000);
            goto label;
        }
        switch (Choice) {
        case 1:
            Dr = "Dr.Ibrahim Eyad";
            Day = weekdays();
            Time = hours();
            break;
        case 2:
            Dr = "Dr.Fawaz Saleh";
            Day = weekdays();
            Time = hours();
            break;
        case 3:
            Dr = "Dr.Bassem Al-Saadi";
            Day = weekdays();
            Time = hours();
            break;
        case 4:
            Dr = "Dr.Anas Ali";
            Day = weekdays();
            Time = hours();
            break;
        }
    };
    void surgery_section() {
        int Choice;
        string Dr;
        string Day;
        string Time;
    label:
        system("cls");

        cout << "\n\n\n\t\t\t\t\t\t\t**Surgery Section**\n";
        cout << "\n\n\t\t\t\t\t\tChoose A Doctor Please.\n";
        cout << "\t\t\t\t\t\t______________________________________________";
        cout << "\n\n\n\t\t\t\t\t\t(1) ~ Dr.Khadija Msaad   ---> Ophthalmology Consultant.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(2) ~ Dr.Mruad Yousef    ---> Optometrist.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(3) ~ Dr.Nouf Hassan     ---> Retinal Consultant.\n\n";
        cout << "\n\n\n\t\t\t\t\t\t(4) ~ Dr.Abdulaziz Ali   ---> Refractive Surgery Consultant.\n\n";
        cout << "\t\t\t\t\t\t______________________________________________\n\n";
        cout << "\t\t\t\t\t\tYour choice? : ";
        cin >> Choice;
        if (!cin.good() || Choice > 4 || Choice < 1) {
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter a Valid Number! ";
            Sleep(4000);
            goto label;
        }
        switch (Choice) {
        case 1:
            Dr = "Dr.Khadija Msaad";
            Day = weekdays();
            Time = hours();
            break;
        case 2:
            Dr = "Dr.Mruad Yousef";
            Day = weekdays();
            Time = hours();
            break;
        case 3:
            Dr = "Dr.Nouf Hassan";
            Day = weekdays();
            Time = hours();
            break;
        case 4:
            Dr = "Dr.Abdulaziz Ali";
            Day = weekdays();
            Time = hours();
            break;
        }
    };

    /*
     ************************************
     *External Functions For Appointment*
     ************************************
     */
    string weekdays() {
        int Choice;
        system("cls");
    label:

        cout << "\n\n\n\t\t\t\t\t\t\tAppointment Schedule\n";
        cout << "\t\t\t\t\t\t______________________________";
        cout << "\n\n\n\t\t\t\t\t\tChoose A day:\n\n";
        cout << "\t\t\t\t\t\t(1) -> Sunday.\n\n";
        cout << "\t\t\t\t\t\t(2) -> Monday.\n\n";
        cout << "\t\t\t\t\t\t(3) -> Tuesday.\n\n";
        cout << "\t\t\t\t\t\t(4) -> Wednesday.\n\n";
        cout << "\t\t\t\t\t\t(5) -> Thursday.\n\n";
        cout << "\t\t\t\t\t\t(6) -> Friday.\n\n";
        cout << "\t\t\t\t\t\t(7) -> Saturday.\n\n";
        cout << "\t\t\t\t\t\t______________________________\n";
        cout << "\t\t\t\t\t\tYour choice? : ";
        cin >> Choice;
        if (!cin.good() || Choice > 7 || Choice < 1) {
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter a Valid Number! ";
            Sleep(4000);
            goto label;
        }
        switch (Choice) {
        case 1:
            return "Sunday";
            break;
        case 2:
            return "Monday";
            break;
        case 3:
            return "Tuesday";
            break;
        case 4:
            return "Wednesday";
            break;
        case 5:
            return "Thursday";
            break;
        case 6:
            return "Friday";
            break;
        case 7:
            return "Saturday";
            break;
        }

    }
    string hours() {
        int Choice;
        system("cls");
    label:

        cout << "\n\n\n\t\t\t\t\t\t\tAppointment Schedule\n";
        cout << "\t\t\t\t\t\t______________________________";
        cout << "\n\n\n\t\t\t\t\t\tChoose The Time:\n\n";
        cout << "\t\t\t\t\t\t(1) -> 08:00 AM to 9:00 AM .\n\n";
        cout << "\t\t\t\t\t\t(2) -> 9:30 AM to 10:30 AM.\n\n";
        cout << "\t\t\t\t\t\t(3) -> 11:00 AM to 12:00 PM.\n\n";
        cout << "\t\t\t\t\t\t(4) -> 12:30 PM to 1:30 PM.\n\n";
        cout << "\t\t\t\t\t\t(5) -> 05:00 PM to 6:00 PM.\n\n";
        cout << "\t\t\t\t\t\t(6) -> 06:30 PM to 07:30 PM.\n\n";
        cout << "\t\t\t\t\t\t(7) -> 08:00 PM to 9:30 PM.\n\n";
        cout << "\t\t\t\t\t\t______________________________\n";
        cout << "\t\t\t\t\t\tYour choice? : ";
        cin >> Choice;
        if (!cin.good() || Choice > 7 || Choice < 1) {
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter a Valid Number! ";
            Sleep(4000);
            goto label;
        }
        switch (Choice) {
        case 1:
            return "08:00 AM to 9:00 AM";
            break;
        case 2:
            return "9:30 AM to 10:30 AM";
            break;
        case 3:
            return "11:00 AM to 12:00 PM";
            break;
        case 4:
            return "12:30 PM to 1:30 PM";
            break;
        case 5:
            return "05:00 PM to 6:00 PM";
            break;
        case 6:
            return "06:30 PM to 07:30 PM";
            break;
        case 7:
            return "08:00 PM to 9:30 PM";
            break;
        }

    }

};

/*
 *********************************
 *Introduction Function Prototype*
 *********************************
 */
void start_screen();



/* Create a connection */


/*
 *********************************************
 *------------> MAIN FUNCTION  <-------------*
 *********************************************
 */
int main() {

    hospital start;

    start_screen();

    char operation;
    do {

        cout << "\n\n\n\t\t\t\t\t\t\tMain Menu\n";
        cout << "\t\t\t\t\t\t______________________________";
        cout << "\n\n\n\t\t\t\t\t\tSelect an option:\n\n";
        cout << "\t\t\t\t\t\t(1) -> Create a file.\n\n";
        cout << "\t\t\t\t\t\t(2) -> Update a file.\n\n";
        cout << "\t\t\t\t\t\t(3) -> Delete a file.\n\n";
        cout << "\t\t\t\t\t\t(4) -> Appointment Management.\n\n";
        cout << "\t\t\t\t\t\t(5) -> Checking for updates.\n\n";
        cout << "\t\t\t\t\t\t(6) -> Log Out.\n\n";
        cout << "\t\t\t\t\t\t______________________________\n";
        cout << "\t\t\t\t\t\tYour choice? : ";
        cin >> operation;
        system("cls");
        switch (operation) {
        case '1':
            start.create_file();
            system("cls");

            cout << endl << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tFile Created Successfully";
            break;
        case '2':
            start.update_file();
            system("cls");

            cout << endl << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tFile Updated Successfully";
            break;
        case '3':
            start.delete_file();
            system("cls");

            cout << endl << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tFile Deleted Successfully";
            break;
        case '4':
            start.appointment_management();
            system("cls");

            cout << endl << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tChanges Have Been Done Successfully";
            break;
        case '5':

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tLooking For Updates...";
            Sleep(5000);
            system("cls");

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tYou are Up To Date !";
            break;
        case '6':

            cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tThanks for using Khaled's Program";
            cout << "\n\n\n\n\t\t\t\t\t\t\t* See you later <3 *";
            break;
        default:

            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tInvalid input \"Enter from 1 - 6\"\n\n\t\t\t\t\t\tPress Enter to repeat.";
        }
        cin.ignore();
        cin.get();
        system("cls");
    } while (operation != '6');

    return 0;
}



/*
 ******************************
 *Introduction Function Header*
 ******************************
 */

void start_screen() {

    char BackgroundNo;
    cout << "\n\n\n\t\t\t\t\t\t***  Welcom to Khaled's Hospital  ***\n";
    cout << "\t\t\t\t\t\t_____________________________________";
    cout << "\n\n\t\t\t\t\t\tChoose a Background Color from below: \n\n";
    cout << "\t\t\t\t\t\t(1) - Red\n\n\t\t\t\t\t\t(2) - Blue\n\n\t\t\t\t\t\t(3) - Green\n\n\t\t\t\t\t\t(4) - Yellow\n\n\t\t\t\t\t\t(5) - Black\n\n\t\t\t\t\t\tYour choice? : ";
    cin >> BackgroundNo;
    switch (BackgroundNo) {
    case '1':
        system("color 4F");
        break;
    case '2':
        system("color 1F");
        break;
    case '3':
        system("color 2F");
        break;
    case '4':
        system("color 6F");
        break;
    case '5':
    default:
        break;
    }
    system("cls");
}