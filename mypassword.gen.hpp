#pragma once
#include <eoslib/types.hpp>
#include <eoslib/message.hpp>
#include <eoslib/datastream.hpp>
#include <eoslib/raw_fwd.hpp>

namespace eosio { namespace raw {
    template<typename Stream> inline void pack( Stream& s, const My_Password::password& value ) {
      raw::pack(s, value.tag);
      raw::pack(s, value.content);
      raw::pack(s, value.owner);
    }
   template<typename Stream> inline void unpack( Stream& s, My_Password::password& value ) {
      raw::unpack(s, value.tag);
      raw::unpack(s, value.content);
      raw::unpack(s, value.owner);
   }   
} }

#include <eoslib/raw.hpp>
namespace eosio {
   void print_ident(int n){while(n-->0){print("  ");}};
   template<typename Type>
   Type current_message_ex() {
      uint32_t size = message_size();
      char* data = (char *)eosio::malloc(size);
      assert(data && read_message(data, size) == size, "error reading message");
      Type value;
      eosio::raw::unpack(data, size, value);
      eosio::free(data);
      return value;
   }

   void dump(const My_Password::password& value, int tab=0) {
      print_ident(tab);print("key:[");prints_l(value.tag.get_data(), value.tag.get_size());print("]\n");
      print_ident(tab);print("value:[");prints_l(value.content.get_data(), value.content.get_size());print("]\n");
      print_ident(tab);print("ower:[", eosio::name(value.owner), "]\n");
   }
   template<>
   My_Password::password current_message<My_Password::password>() {
      return current_message_ex<My_Password::password>();
   }
} //eosio

