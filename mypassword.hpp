/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eoslib/eos.hpp>
#include <eoslib/db.hpp>
#include <eoslib/string.hpp>


namespace My_Password {
    struct PACKED(password){
        eosio::string tag;
        eosio::string content;
        account_name  owner;
    };
    using passwords = eosio::table<N(mypassword),N(mypassword),N(passwords),password,char*>;
}