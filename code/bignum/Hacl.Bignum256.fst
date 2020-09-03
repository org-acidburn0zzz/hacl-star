module Hacl.Bignum256

open FStar.Mul

module BN = Hacl.Bignum
module BM = Hacl.Bignum.Montgomery
module BE = Hacl.Bignum.Exponentiation

friend Hacl.Bignum.Exponentiation

#set-options "--z3rlimit 50 --fuel 0 --ifuel 0"

let _ = assert_norm (256ul = 64ul `FStar.UInt32.mul` 4ul)

/// A note about the style of normalization used in this file. Normally,
/// bn_sub_eq_len and others would be marked as inline_for_extraction. However,
/// we want to keep a copy of the functions that take the nLen parameter at
/// runtime, meaning we can't blindly mark everything as inline_for_extraction,
/// otherwise the copy of the code that a runtime-parametric over the length
/// would be horrendous. So instead we do the inline_by_extraction "by hand" via
/// a call to `norm`. Note that these are all partial applications, meaning that
/// we normalize pure terms.


let add = Hacl.Bignum.Addition.bn_add_eq_len n_limbs

let sub = Hacl.Bignum.Addition.bn_sub_eq_len n_limbs

let mul (a b: lbignum n_limbs): BN.bn_karatsuba_mul_st a b =
  BN.bn_mul n_limbs a n_limbs b

let bit_set: BN.bn_set_ith_bit_st n_limbs =
  BN.(norm [ zeta; primops; iota; delta_only [ `%bn_set_ith_bit ] ] (bn_set_ith_bit n_limbs))

let add_mod_n: BN.bn_add_mod_n_st n_limbs =
  BN.bn_add_mod_n n_limbs

let sub_mask: BN.bn_sub_mask_st n_limbs =
  BN.bn_sub_mask n_limbs

let sqr (a: lbignum n_limbs): BN.bn_karatsuba_sqr_st a =
  //BN.bn_sqr n_limbs a
  BN.bn_mul n_limbs a n_limbs a

inline_for_extraction noextract
instance bn_inst: BN.bn n_limbs = {
  BN.bit_set;
  BN.add_mod_n;
  BN.mul;
  BN.sqr;
  BN.sub_mask
}

let precomp: BM.precomp_r2_mod_n_st n_limbs =
  BM.precomp_r2_mod_n #n_limbs #bn_inst

let reduction: BM.mont_reduction_st n_limbs =
  BM.mont_reduction n_limbs

let to: BM.to_mont_st n_limbs =
  BM.to_mont #n_limbs #bn_inst reduction

let from: BM.from_mont_st n_limbs =
  BM.from_mont #n_limbs reduction

let mont_mul: BM.mont_mul_st n_limbs =
  BM.mont_mul #n_limbs #bn_inst reduction

let mont_sqr: BM.mont_sqr_st n_limbs =
  BM.mont_sqr #n_limbs #bn_inst reduction

inline_for_extraction noextract
instance mont_inst: BM.mont n_limbs = {
  BM.bn = FStar.Tactics.Typeclasses.solve;
  BM.precomp;
  BM.reduction;
  BM.to;
  BM.from;
  BM.mul = mont_mul;
  BM.sqr = mont_sqr;
}

let mod_exp_loop: BE.bn_mod_exp_loop_st n_limbs =
  norm [ zeta; primops; iota; delta_only [ `%BE.bn_mod_exp_loop ] ] (BE.bn_mod_exp_loop n_limbs #mont_inst)

let mod_exp =
  BE.mk_bn_mod_exp 256ul n_limbs #mont_inst mod_exp_loop

let mod_exp_mont_ladder_loop: BE.bn_mod_exp_mont_ladder_loop_st n_limbs =
  norm [ zeta; primops; iota; delta_only [ `%BE.bn_mod_exp_mont_ladder_loop ] ] (BE.bn_mod_exp_mont_ladder_loop n_limbs #mont_inst)

let mod_exp_mont_ladder =
  BE.mk_bn_mod_exp_mont_ladder 256ul n_limbs #mont_inst mod_exp_mont_ladder_loop

let new_bn_from_bytes_be = Hacl.Bignum.Convert.new_bn_from_bytes_be

let bn_to_bytes_be = Hacl.Bignum.Convert.mk_bn_to_bytes_be n_bytes

let lt_mask = Hacl.Bignum.mk_bn_lt_mask n_limbs