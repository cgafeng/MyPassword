/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <mypassword.hpp>
#include <mypassword.gen.hpp>
namespace My_Password {
    void apply_add_password(const My_Password::addpassword& newpassword)
    {
        eosio::print("add password");
        eosio::dump(newpassword);
        eosio::require_auth(newpassword.owner);

        char tmp[1024];
        int32_t load_len = load_str (newpassword.owner, N(mypassword), N(mypasswords),
            (char *)newpassword.tag.get_data(), newpassword.tag.get_size(),
            tmp, 1024);
        assert(load_len == -1, "password already exists");

        bytes b = eosio::raw::pack(newpassword.content);
        uint32_t err = store_str( newpassword.owner, N(mypasswords),
            (char *)newpassword.tag.get_data(), newpassword.tag.get_size(),
            (char *)b.data, b.len);
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
           My_Password::apply_add_password(eosio::current_message<My_Password::addpassword>());
       }
    }

} // extern "C"
