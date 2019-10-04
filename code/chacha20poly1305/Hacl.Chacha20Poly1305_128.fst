module Hacl.Chacha20Poly1305_128


open Hacl.Meta.Chacha20Poly1305
open Hacl.Impl.Chacha20Poly1305
open Hacl.Impl.Poly1305.Fields

#set-options "--z3rlimit 50 --max_fuel 0 --max_ifuel 0"

private
let poly1305_padded_128 = poly1305_padded_higher #M128
private
let poly1305_do_128 = poly1305_do_higher #M128 poly1305_padded_128

let aead_encrypt : aead_encrypt_st M128 =
  aead_encrypt_higher #M128 poly1305_do_128 Hacl.Chacha20.Vec128.chacha20_encrypt_128

let aead_decrypt : aead_decrypt_st M128 =
  aead_decrypt_higher #M128 Hacl.Chacha20.Vec128.chacha20_encrypt_128 poly1305_do_128
