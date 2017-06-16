#include <iostream>
#include <"model.h">
#include <"controller.h">

#include <"mysql_connection.h">

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int main() {

    sql::mysql::Driver * sql::mysql::driver;
    sql:: *con;
    sql::mysql::
    sql::mysql::driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "user", "password");

    delete con;
}