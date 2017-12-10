/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eoslib/eos.hpp>
#include <eoslib/db.hpp>
#include <eoslib/string.hpp>


namespace My_Password {
    struct addpassword {
        eosio::string tag;
        eosio::string content;
        account_name  owner;
    };
    struct delpassword{
        eosio::string tag;
        account_name  owner;
    };
    struct PACKED(password){
        eosio::string tag;
        eosio::string content;
    };
}