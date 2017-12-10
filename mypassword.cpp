/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <mypassword.hpp>
#include <mypassword.gen.hpp>
namespace My_Password {
    void apply_add_password(const My_Password::password& newpassword)
    {
        eosio::print("add password");
        eosio::dump(newpassword);
    }
}
/**
 *  The init() and apply() methods must have C calling convention so that the blockchain can lookup and
 *  call these methods.
 */
extern "C" {

    /**
     *  This method is called once when the contract is published or updated.
     */
    void init()  {
       eosio::print( "Init MyPassword!\n" );
    }

    /// The apply method implements the dispatch of events to this contract
    void apply( uint64_t code, uint64_t action ) {
       eosio::print( "Hello MyPassword: ", eosio::name(code), "->", eosio::name(action), "\n" );
       if (action == N(addpassword))
       {
           My_Password::apply_add_password(eosio::current_message<My_Password::password>());
       }
    }

} // extern "C"
