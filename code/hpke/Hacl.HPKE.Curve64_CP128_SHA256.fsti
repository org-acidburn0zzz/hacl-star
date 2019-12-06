module Hacl.HPKE.Curve64_CP128_SHA256

open Hacl.Impl.HPKE
module DH = Spec.Agile.DH
module AEAD = Spec.Agile.AEAD
module Hash = Spec.Agile.Hash

noextract unfold
let cs = (DH.DH_Curve25519, AEAD.CHACHA20_POLY1305, Hash.SHA2_256)

val setupBaseI: setupBaseI_st cs

val setupBaseR: setupBaseR_st cs

val sealBase: sealBase_st cs

val openBase: openBase_st cs