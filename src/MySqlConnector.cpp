//
// Created by mwo on 7/01/17.
//

#include "MySqlConnector.h"

#include <mysql++/mysql++.h>
#include <mysql++/ssqls.h>


#include <iostream>
#include <memory>


namespace xmreg {


string MySqlConnector::url;
size_t MySqlConnector::port;
string MySqlConnector::username;
string MySqlConnector::password;
string MySqlConnector::dbname;

MySqlConnector::MySqlConnector()
{
    if (!connect())
        throw std::runtime_error("Connection to Mysql failed!");
}

bool
MySqlConnector::connect()
{
    if (conn.connected())
        return true;

    try
    {
        if (!conn.connect(dbname.c_str(), url.c_str(),
                          username.c_str(), password.c_str(),
                          port))
        {
            cerr << "Connection to Mysql failed!" << endl;
            return false;
        }
    }
    catch (mysqlpp::ConnectionFailed const& e)
    {
        MYSQL_EXCEPTION_MSG(e);
        return false;
    }
    catch (std::exception const& e)
    {
        cerr << e.what() << '\n';
        return false;
    }
    catch (...)
    {
        cerr << "Unknown exception in MySqlConnector::connect()" << '\n';
        return false;
    }

    return true;
}


bool
MySqlConnector::ping()
{
    return conn.ping();
}

Query
MySqlConnector::query(const char *qstr)
{
    return conn.query(qstr);
}

Query
MySqlConnector::query(const std::string &qstr)
{
    return conn.query(qstr);
}

Connection&
MySqlConnector::get_connection()
{
    return conn;
}

MySqlConnector::~MySqlConnector()
{
    conn.disconnect();
};

}