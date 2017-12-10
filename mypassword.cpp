/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <mypassword.hpp>
#include <mypassword.gen.hpp>
namespace My_Password {
    const static uint32_t MAX_STRING_LEN = 1024;
    const static auto CODE_NAME = N(mypassword);
    const static auto TABLE_NAME = N(mypasswords);
    void apply_add_password(const My_Password::addpassword& newpassword)
    {
        eosio::print("add password");
        eosio::dump(newpassword);
        eosio::require_auth(newpassword.owner);

        char tmp[MAX_STRING_LEN];
        int32_t load_len = load_str(newpassword.owner, CODE_NAME, TABLE_NAME,
                                    (char *)newpassword.tag.get_data(), newpassword.tag.get_size(),
                                    tmp, MAX_STRING_LEN);
        assert(load_len == -1, "password already exists");

        bytes b = eosio::raw::pack(newpassword.content);
        uint32_t err = store_str(newpassword.owner, TABLE_NAME,
                                 (char *)newpassword.tag.get_data(), newpassword.tag.get_size(),
                                 (char *)b.data, b.len);
    }

    void apply_change_password(const My_Password::addpassword& newpassword)
    {
        eosio::print("change password");
        eosio::dump(newpassword);
        eosio::require_auth(newpassword.owner);

        char tmp[MAX_STRING_LEN];
        int32_t load_len = load_str(newpassword.owner, CODE_NAME, TABLE_NAME,
                                    (char *)newpassword.tag.get_data(), newpassword.tag.get_size(),
                                    tmp, MAX_STRING_LEN);
        assert(load_len != -1, "password not exists");

        bytes b = eosio::raw::pack(newpassword.content);
        uint32_t err = store_str(newpassword.owner, TABLE_NAME,
                                 (char *)newpassword.tag.get_data(), newpassword.tag.get_size(),
                                 (char *)b.data, b.len);
    }

    void apply_del_password(const My_Password::delpassword &passwordinfo)
    {
        eosio::print("delete password");
        eosio::dump(passwordinfo);
        eosio::require_auth(passwordinfo.owner);

        char tmp[MAX_STRING_LEN];
        int32_t load_len = load_str(passwordinfo.owner, CODE_NAME, TABLE_NAME,
                                    (char *)passwordinfo.tag.get_data(), passwordinfo.tag.get_size(),
                                    tmp, MAX_STRING_LEN);
        assert(load_len != -1, "password not exists");

        uint32_t err = remove_str(passwordinfo.owner, TABLE_NAME,
                                  (char *)passwordinfo.tag.get_data(), passwordinfo.tag.get_size());
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
       else if(action == N(resetpassword))
       {
           My_Password::apply_change_password(eosio::current_message<My_Password::addpassword>());
       }
       else if(action == N(delpassword))
       {
           My_Password::apply_del_password(eosio::current_message<My_Password::delpassword>());
       }
    }

} // extern "C"
