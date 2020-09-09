/* MIT License
 *
 * Copyright (c) 2016-2020 INRIA, CMU and Microsoft Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#include "Hacl_Bignum4096.h"

/************************/
/* Arithmetic functions */
/************************/


/*
Write `a + b mod 2^4096` in `res`.

  This functions returns the carry.

  The arguments a, b and res are meant to be 4096-bit bignums, i.e. uint64_t[64]
*/
uint64_t Hacl_Bignum4096_add(uint64_t *a, uint64_t *b, uint64_t *res)
{
  uint64_t c = (uint64_t)0U;
  uint32_t k = (uint32_t)64U;
  for (uint32_t i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
  {
    uint64_t t1 = a[(uint32_t)4U * i];
    uint64_t t20 = b[(uint32_t)4U * i];
    c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t1, t20, res + (uint32_t)4U * i);
    uint64_t t10 = a[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = b[(uint32_t)4U * i + (uint32_t)1U];
    c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t10, t21, res + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t11 = a[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = b[(uint32_t)4U * i + (uint32_t)2U];
    c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t11, t22, res + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t12 = a[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = b[(uint32_t)4U * i + (uint32_t)3U];
    c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t12, t2, res + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k; i < (uint32_t)64U; i++)
  {
    uint64_t t1 = a[i];
    uint64_t t2 = b[i];
    c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t1, t2, res + i);
  }
  return c;
}

/*
Write `a - b mod 2^4096` in `res`.

  This functions returns the carry.

  The arguments a, b and res are meant to be 4096-bit bignums, i.e. uint64_t[64]
*/
uint64_t Hacl_Bignum4096_sub(uint64_t *a, uint64_t *b, uint64_t *res)
{
  uint64_t c = (uint64_t)0U;
  uint32_t k = (uint32_t)64U;
  for (uint32_t i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
  {
    uint64_t t1 = a[(uint32_t)4U * i];
    uint64_t t20 = b[(uint32_t)4U * i];
    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t1, t20, res + (uint32_t)4U * i);
    uint64_t t10 = a[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = b[(uint32_t)4U * i + (uint32_t)1U];
    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t10, t21, res + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t11 = a[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = b[(uint32_t)4U * i + (uint32_t)2U];
    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t11, t22, res + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t12 = a[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = b[(uint32_t)4U * i + (uint32_t)3U];
    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t12, t2, res + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k; i < (uint32_t)64U; i++)
  {
    uint64_t t1 = a[i];
    uint64_t t2 = b[i];
    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t1, t2, res + i);
  }
  return c;
}

/*
Write `a * b` in `res`.

  The arguments a and b are meant to be 4096-bit bignums, i.e. uint64_t[64].
  The outparam res is meant to be a 8192-bit bignum, i.e. uint64_t[128].
*/
void Hacl_Bignum4096_mul(uint64_t *a, uint64_t *b, uint64_t *res)
{
  uint32_t resLen = (uint32_t)128U;
  memset(res, 0U, resLen * sizeof (uint64_t));
  for (uint32_t i0 = (uint32_t)0U; i0 < (uint32_t)64U; i0++)
  {
    uint64_t uu____0 = b[i0];
    uint64_t *res_ = res + i0;
    uint64_t c = (uint64_t)0U;
    uint32_t k = (uint32_t)64U;
    for (uint32_t i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
    {
      c =
        Hacl_Bignum_Multiplication_mul_carry_add_u64_st(c,
          a[(uint32_t)4U * i],
          uu____0,
          res_ + (uint32_t)4U * i);
      c =
        Hacl_Bignum_Multiplication_mul_carry_add_u64_st(c,
          a[(uint32_t)4U * i + (uint32_t)1U],
          uu____0,
          res_ + (uint32_t)4U * i + (uint32_t)1U);
      c =
        Hacl_Bignum_Multiplication_mul_carry_add_u64_st(c,
          a[(uint32_t)4U * i + (uint32_t)2U],
          uu____0,
          res_ + (uint32_t)4U * i + (uint32_t)2U);
      c =
        Hacl_Bignum_Multiplication_mul_carry_add_u64_st(c,
          a[(uint32_t)4U * i + (uint32_t)3U],
          uu____0,
          res_ + (uint32_t)4U * i + (uint32_t)3U);
    }
    for (uint32_t i = k; i < (uint32_t)64U; i++)
    {
      c = Hacl_Bignum_Multiplication_mul_carry_add_u64_st(c, a[i], uu____0, res_ + i);
    }
    uint64_t r = c;
    res[(uint32_t)64U + i0] = r;
  }
}

static void bit_set(uint64_t *input, uint32_t ind)
{
  uint32_t i = ind / (uint32_t)64U;
  uint32_t j = ind % (uint32_t)64U;
  input[i] = input[i] | (uint64_t)1U << j;
}

static void add_mod_n(uint64_t *n, uint64_t *a, uint64_t *b, uint64_t *res)
{
  uint64_t c0 = (uint64_t)0U;
  uint32_t k0 = (uint32_t)64U;
  for (uint32_t i = (uint32_t)0U; i < k0 / (uint32_t)4U; i++)
  {
    uint64_t t1 = a[(uint32_t)4U * i];
    uint64_t t20 = b[(uint32_t)4U * i];
    c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, t1, t20, res + (uint32_t)4U * i);
    uint64_t t10 = a[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = b[(uint32_t)4U * i + (uint32_t)1U];
    c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, t10, t21, res + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t11 = a[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = b[(uint32_t)4U * i + (uint32_t)2U];
    c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, t11, t22, res + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t12 = a[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = b[(uint32_t)4U * i + (uint32_t)3U];
    c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, t12, t2, res + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k0; i < (uint32_t)64U; i++)
  {
    uint64_t t1 = a[i];
    uint64_t t2 = b[i];
    c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, t1, t2, res + i);
  }
  uint64_t c00 = c0;
  uint64_t tmp[64U] = { 0U };
  uint64_t c = (uint64_t)0U;
  uint32_t k = (uint32_t)64U;
  for (uint32_t i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
  {
    uint64_t t1 = res[(uint32_t)4U * i];
    uint64_t t20 = n[(uint32_t)4U * i];
    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t1, t20, tmp + (uint32_t)4U * i);
    uint64_t t10 = res[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = n[(uint32_t)4U * i + (uint32_t)1U];
    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t10, t21, tmp + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t11 = res[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = n[(uint32_t)4U * i + (uint32_t)2U];
    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t11, t22, tmp + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t12 = res[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = n[(uint32_t)4U * i + (uint32_t)3U];
    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t12, t2, tmp + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k; i < (uint32_t)64U; i++)
  {
    uint64_t t1 = res[i];
    uint64_t t2 = n[i];
    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t1, t2, tmp + i);
  }
  uint64_t c1 = c;
  uint64_t c2 = c00 - c1;
  for (uint32_t i = (uint32_t)0U; i < (uint32_t)64U; i++)
  {
    uint64_t *os = res;
    uint64_t x = (c2 & res[i]) | (~c2 & tmp[i]);
    os[i] = x;
  }
}

static void sqr(uint64_t *a, uint64_t *res)
{
  uint32_t resLen = (uint32_t)128U;
  memset(res, 0U, resLen * sizeof (uint64_t));
  for (uint32_t i0 = (uint32_t)0U; i0 < (uint32_t)64U; i0++)
  {
    uint64_t uu____0 = a[i0];
    uint64_t *res_ = res + i0;
    uint64_t c = (uint64_t)0U;
    uint32_t k = (uint32_t)64U;
    for (uint32_t i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
    {
      c =
        Hacl_Bignum_Multiplication_mul_carry_add_u64_st(c,
          a[(uint32_t)4U * i],
          uu____0,
          res_ + (uint32_t)4U * i);
      c =
        Hacl_Bignum_Multiplication_mul_carry_add_u64_st(c,
          a[(uint32_t)4U * i + (uint32_t)1U],
          uu____0,
          res_ + (uint32_t)4U * i + (uint32_t)1U);
      c =
        Hacl_Bignum_Multiplication_mul_carry_add_u64_st(c,
          a[(uint32_t)4U * i + (uint32_t)2U],
          uu____0,
          res_ + (uint32_t)4U * i + (uint32_t)2U);
      c =
        Hacl_Bignum_Multiplication_mul_carry_add_u64_st(c,
          a[(uint32_t)4U * i + (uint32_t)3U],
          uu____0,
          res_ + (uint32_t)4U * i + (uint32_t)3U);
    }
    for (uint32_t i = k; i < (uint32_t)64U; i++)
    {
      c = Hacl_Bignum_Multiplication_mul_carry_add_u64_st(c, a[i], uu____0, res_ + i);
    }
    uint64_t r = c;
    res[(uint32_t)64U + i0] = r;
  }
}

static void precomp(uint64_t *n, uint64_t *res)
{
  uint64_t bn_zero[64U] = { 0U };
  uint64_t mask = (uint64_t)0xFFFFFFFFFFFFFFFFU;
  for (uint32_t i = (uint32_t)0U; i < (uint32_t)64U; i++)
  {
    uint64_t uu____0 = FStar_UInt64_eq_mask(n[i], bn_zero[i]);
    mask = uu____0 & mask;
  }
  uint64_t mask10 = mask;
  uint64_t res1 = mask10;
  uint64_t mask0 = res1;
  uint32_t bits;
  if (mask0 == (uint64_t)0U)
  {
    uint32_t priv0 = (uint32_t)0U;
    for (uint32_t i = (uint32_t)0U; i < (uint32_t)64U; i++)
    {
      uint64_t mask1 = FStar_UInt64_eq_mask(n[i], (uint64_t)0U);
      uint32_t ite;
      if (mask1 == (uint64_t)0U)
      {
        ite = i;
      }
      else
      {
        ite = priv0;
      }
      priv0 = ite;
    }
    uint32_t ind = priv0;
    uint64_t uu____1 = n[ind];
    uint32_t priv = (uint32_t)0U;
    for (uint32_t i = (uint32_t)0U; i < (uint32_t)64U; i++)
    {
      uint64_t bit_i = uu____1 >> i & (uint64_t)1U;
      uint32_t ite;
      if (bit_i == (uint64_t)1U)
      {
        ite = i;
      }
      else
      {
        ite = priv;
      }
      priv = ite;
    }
    uint32_t bits0 = priv;
    bits = (uint32_t)64U * ind + bits0;
  }
  else
  {
    bits = (uint32_t)0U;
  }
  memset(res, 0U, (uint32_t)64U * sizeof (uint64_t));
  bit_set(res, bits);
  for (uint32_t i = (uint32_t)0U; i < (uint32_t)8192U - bits; i++)
  {
    add_mod_n(n, res, res, res);
  }
}

static void reduction(uint64_t *n, uint64_t nInv_u64, uint64_t *c, uint64_t *res)
{
  uint64_t c0 = (uint64_t)0U;
  for (uint32_t i0 = (uint32_t)0U; i0 < (uint32_t)64U; i0++)
  {
    uint64_t qj = nInv_u64 * c[i0];
    uint64_t *res_ = c + i0;
    uint64_t c1 = (uint64_t)0U;
    uint32_t k = (uint32_t)64U;
    for (uint32_t i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
    {
      c1 =
        Hacl_Bignum_Multiplication_mul_carry_add_u64_st(c1,
          n[(uint32_t)4U * i],
          qj,
          res_ + (uint32_t)4U * i);
      c1 =
        Hacl_Bignum_Multiplication_mul_carry_add_u64_st(c1,
          n[(uint32_t)4U * i + (uint32_t)1U],
          qj,
          res_ + (uint32_t)4U * i + (uint32_t)1U);
      c1 =
        Hacl_Bignum_Multiplication_mul_carry_add_u64_st(c1,
          n[(uint32_t)4U * i + (uint32_t)2U],
          qj,
          res_ + (uint32_t)4U * i + (uint32_t)2U);
      c1 =
        Hacl_Bignum_Multiplication_mul_carry_add_u64_st(c1,
          n[(uint32_t)4U * i + (uint32_t)3U],
          qj,
          res_ + (uint32_t)4U * i + (uint32_t)3U);
    }
    for (uint32_t i = k; i < (uint32_t)64U; i++)
    {
      c1 = Hacl_Bignum_Multiplication_mul_carry_add_u64_st(c1, n[i], qj, res_ + i);
    }
    uint64_t r = c1;
    uint64_t c10 = r;
    c0 =
      Lib_IntTypes_Intrinsics_add_carry_u64(c0,
        c10,
        c[(uint32_t)64U + i0],
        c + (uint32_t)64U + i0);
  }
  memcpy(res, c + (uint32_t)64U, (uint32_t)64U * sizeof (uint64_t));
  uint64_t uu____0 = c0;
  uint64_t tmp[64U] = { 0U };
  uint64_t c1 = (uint64_t)0U;
  uint32_t k = (uint32_t)64U;
  for (uint32_t i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
  {
    uint64_t t1 = res[(uint32_t)4U * i];
    uint64_t t20 = n[(uint32_t)4U * i];
    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t1, t20, tmp + (uint32_t)4U * i);
    uint64_t t10 = res[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = n[(uint32_t)4U * i + (uint32_t)1U];
    c1 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c1,
        t10,
        t21,
        tmp + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t11 = res[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = n[(uint32_t)4U * i + (uint32_t)2U];
    c1 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c1,
        t11,
        t22,
        tmp + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t12 = res[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = n[(uint32_t)4U * i + (uint32_t)3U];
    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t12, t2, tmp + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k; i < (uint32_t)64U; i++)
  {
    uint64_t t1 = res[i];
    uint64_t t2 = n[i];
    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t1, t2, tmp + i);
  }
  uint64_t c10 = c1;
  uint64_t c2 = uu____0 - c10;
  for (uint32_t i = (uint32_t)0U; i < (uint32_t)64U; i++)
  {
    uint64_t *os = res;
    uint64_t x = (c2 & res[i]) | (~c2 & tmp[i]);
    os[i] = x;
  }
}

static void to(uint64_t *n, uint64_t nInv_u64, uint64_t *r2, uint64_t *a, uint64_t *aM)
{
  uint64_t c[128U] = { 0U };
  Hacl_Bignum4096_mul(a, r2, c);
  reduction(n, nInv_u64, c, aM);
}

static void from(uint64_t *n, uint64_t nInv_u64, uint64_t *aM, uint64_t *a)
{
  uint64_t tmp[128U] = { 0U };
  memcpy(tmp, aM, (uint32_t)64U * sizeof (uint64_t));
  reduction(n, nInv_u64, tmp, a);
}

static void
mont_mul(uint64_t *n, uint64_t nInv_u64, uint64_t *aM, uint64_t *bM, uint64_t *resM)
{
  uint64_t c[128U] = { 0U };
  Hacl_Bignum4096_mul(aM, bM, c);
  reduction(n, nInv_u64, c, resM);
}

static void mont_sqr(uint64_t *n, uint64_t nInv_u64, uint64_t *aM, uint64_t *resM)
{
  uint64_t c[128U] = { 0U };
  sqr(aM, c);
  reduction(n, nInv_u64, c, resM);
}

/*
Write `a mod n` in `res` if a < n * n.

  The argument a is meant to be a 8192-bit bignum, i.e. uint64_t[128].
  The argument n, r2 and the outparam res are meant to be a 4096-bit bignum, i.e. uint64_t[64].
  The argument r2 is a precomputed constant 2 ^ 8192 mod n.
*/
void Hacl_Bignum4096_mod_precompr2(uint64_t *n, uint64_t *a, uint64_t *r2, uint64_t *res)
{
  uint64_t a_mod[64U] = { 0U };
  uint64_t a1[128U] = { 0U };
  memcpy(a1, a, (uint32_t)128U * sizeof (uint64_t));
  uint64_t mu = Hacl_Bignum_ModInv64_mod_inv_u64(n[0U]);
  reduction(n, mu, a1, a_mod);
  to(n, mu, r2, a_mod, res);
}

/*
Write `a mod n` in `res` if a < n * n.

  The argument a is meant to be a 8192-bit bignum, i.e. uint64_t[128].
  The argument n and the outparam res are meant to be a 4096-bit bignum, i.e. uint64_t[64].
*/
void Hacl_Bignum4096_mod(uint64_t *n, uint64_t *a, uint64_t *res)
{
  uint64_t r2[64U] = { 0U };
  precomp(n, r2);
  uint64_t a_mod[64U] = { 0U };
  uint64_t a1[128U] = { 0U };
  memcpy(a1, a, (uint32_t)128U * sizeof (uint64_t));
  uint64_t mu = Hacl_Bignum_ModInv64_mod_inv_u64(n[0U]);
  reduction(n, mu, a1, a_mod);
  to(n, mu, r2, a_mod, res);
}

static void
mod_exp_loop(
  uint64_t *n,
  uint64_t nInv_u64,
  uint32_t bBits,
  uint32_t bLen,
  uint64_t *b,
  uint64_t *aM,
  uint64_t *accM
)
{
  for (uint32_t i = (uint32_t)0U; i < bBits; i++)
  {
    uint64_t get_bit = Hacl_Bignum_bn_get_ith_bit(bLen, b, i);
    if (get_bit == (uint64_t)1U)
    {
      mont_mul(n, nInv_u64, aM, accM, accM);
    }
    mont_sqr(n, nInv_u64, aM, aM);
  }
}

/*
Write `a ^ b mod n` in `res`.

  The arguments a, n, r2 and the outparam res are meant to be 4096-bit bignums, i.e. uint64_t[64].
  The argument r2 is a precomputed constant 2 ^ 8192 mod n.
  The argument b is a bignum of any size, and bBits is an upper bound on the
  number of significant bits of b. For instance, if b is a 4096-bit bignum,
  bBits should be 4096. The function is *NOT* constant-time on the argument b.
*/
void
Hacl_Bignum4096_mod_exp_precompr2(
  uint64_t *n,
  uint64_t *a,
  uint32_t bBits,
  uint64_t *b,
  uint64_t *r2,
  uint64_t *res
)
{
  uint64_t acc[64U] = { 0U };
  memset(acc, 0U, (uint32_t)64U * sizeof (uint64_t));
  acc[0U] = (uint64_t)1U;
  uint32_t bLen = (bBits - (uint32_t)1U) / (uint32_t)64U + (uint32_t)1U;
  uint64_t nInv_u64 = Hacl_Bignum_ModInv64_mod_inv_u64(n[0U]);
  uint64_t aM[64U] = { 0U };
  uint64_t accM[64U] = { 0U };
  to(n, nInv_u64, r2, a, aM);
  to(n, nInv_u64, r2, acc, accM);
  mod_exp_loop(n, nInv_u64, bBits, bLen, b, aM, accM);
  from(n, nInv_u64, accM, res);
}

/*
Write `a ^ b mod n` in `res`.

  The arguments a, n and the outparam res are meant to be 4096-bit bignums, i.e. uint64_t[64].
  The argument b is a bignum of any size, and bBits is an upper bound on the
  number of significant bits of b. For instance, if b is a 4096-bit bignum,
  bBits should be 4096. The function is *NOT* constant-time on the argument b.
*/
void
Hacl_Bignum4096_mod_exp(uint64_t *n, uint64_t *a, uint32_t bBits, uint64_t *b, uint64_t *res)
{
  uint64_t r2[64U] = { 0U };
  precomp(n, r2);
  uint64_t acc[64U] = { 0U };
  memset(acc, 0U, (uint32_t)64U * sizeof (uint64_t));
  acc[0U] = (uint64_t)1U;
  uint32_t bLen = (bBits - (uint32_t)1U) / (uint32_t)64U + (uint32_t)1U;
  uint64_t nInv_u64 = Hacl_Bignum_ModInv64_mod_inv_u64(n[0U]);
  uint64_t aM[64U] = { 0U };
  uint64_t accM[64U] = { 0U };
  to(n, nInv_u64, r2, a, aM);
  to(n, nInv_u64, r2, acc, accM);
  mod_exp_loop(n, nInv_u64, bBits, bLen, b, aM, accM);
  from(n, nInv_u64, accM, res);
}

static void
mod_exp_mont_ladder_loop(
  uint64_t *n,
  uint64_t nInv_u64,
  uint32_t bBits,
  uint32_t bLen,
  uint64_t *b,
  uint64_t *rM0,
  uint64_t *rM1,
  uint64_t *sw
)
{
  for (uint32_t i0 = (uint32_t)0U; i0 < bBits; i0++)
  {
    uint64_t bit = Hacl_Bignum_bn_get_ith_bit(bLen, b, bBits - i0 - (uint32_t)1U);
    uint64_t sw1 = bit ^ sw[0U];
    for (uint32_t i = (uint32_t)0U; i < (uint32_t)64U; i++)
    {
      uint64_t dummy = ((uint64_t)0U - sw1) & (rM0[i] ^ rM1[i]);
      rM0[i] = rM0[i] ^ dummy;
      rM1[i] = rM1[i] ^ dummy;
    }
    mont_mul(n, nInv_u64, rM1, rM0, rM1);
    mont_sqr(n, nInv_u64, rM0, rM0);
    sw[0U] = bit;
  }
}

/*
Write `a ^ b mod n` in `res`.

  The arguments a, n, r2 and the outparam res are meant to be 4096-bit bignums, i.e. uint64_t[64].
  The argument r2 is a precomputed constant 2 ^ 8192 mod n.
  The argument b is a bignum of any size, and bBits is an upper bound on the
  number of significant bits of b. For instance, if b is a 4096-bit bignum,
  bBits should be 4096. The function is constant-time on the argument b.
*/
void
Hacl_Bignum4096_mod_exp_mont_ladder_precompr2(
  uint64_t *n,
  uint64_t *a,
  uint32_t bBits,
  uint64_t *b,
  uint64_t *r2,
  uint64_t *res
)
{
  uint64_t one[64U] = { 0U };
  memset(one, 0U, (uint32_t)64U * sizeof (uint64_t));
  one[0U] = (uint64_t)1U;
  uint32_t bLen = (bBits - (uint32_t)1U) / (uint32_t)64U + (uint32_t)1U;
  uint64_t nInv_u64 = Hacl_Bignum_ModInv64_mod_inv_u64(n[0U]);
  uint64_t rM0[64U] = { 0U };
  uint64_t rM1[64U] = { 0U };
  uint64_t sw = (uint64_t)0U;
  to(n, nInv_u64, r2, one, rM0);
  to(n, nInv_u64, r2, a, rM1);
  mod_exp_mont_ladder_loop(n, nInv_u64, bBits, bLen, b, rM0, rM1, &sw);
  uint64_t uu____0 = sw;
  for (uint32_t i = (uint32_t)0U; i < (uint32_t)64U; i++)
  {
    uint64_t dummy = ((uint64_t)0U - uu____0) & (rM0[i] ^ rM1[i]);
    rM0[i] = rM0[i] ^ dummy;
    rM1[i] = rM1[i] ^ dummy;
  }
  from(n, nInv_u64, rM0, res);
}

/*
Write `a ^ b mod n` in `res`.

  The arguments a, n and the outparam res are meant to be 4096-bit bignums, i.e. uint64_t[64].
  The argument b is a bignum of any size, and bBits is an upper bound on the
  number of significant bits of b. For instance, if b is a 4096-bit bignum,
  bBits should be 4096. The function is constant-time on the argument b.
*/
void
Hacl_Bignum4096_mod_exp_mont_ladder(
  uint64_t *n,
  uint64_t *a,
  uint32_t bBits,
  uint64_t *b,
  uint64_t *res
)
{
  uint64_t r2[64U] = { 0U };
  precomp(n, r2);
  uint64_t one[64U] = { 0U };
  memset(one, 0U, (uint32_t)64U * sizeof (uint64_t));
  one[0U] = (uint64_t)1U;
  uint32_t bLen = (bBits - (uint32_t)1U) / (uint32_t)64U + (uint32_t)1U;
  uint64_t nInv_u64 = Hacl_Bignum_ModInv64_mod_inv_u64(n[0U]);
  uint64_t rM0[64U] = { 0U };
  uint64_t rM1[64U] = { 0U };
  uint64_t sw = (uint64_t)0U;
  to(n, nInv_u64, r2, one, rM0);
  to(n, nInv_u64, r2, a, rM1);
  mod_exp_mont_ladder_loop(n, nInv_u64, bBits, bLen, b, rM0, rM1, &sw);
  uint64_t uu____0 = sw;
  for (uint32_t i = (uint32_t)0U; i < (uint32_t)64U; i++)
  {
    uint64_t dummy = ((uint64_t)0U - uu____0) & (rM0[i] ^ rM1[i]);
    rM0[i] = rM0[i] ^ dummy;
    rM1[i] = rM1[i] ^ dummy;
  }
  from(n, nInv_u64, rM0, res);
}

/*
Compute `2 ^ (128 * nLen) mod n`.

  The argument n points to a bignum of size nLen of valid memory.
  The function returns a heap-allocated bignum of size nLen,
   or NULL if either the allocation failed, or the amount of
    required memory would exceed 4GB.

  If the return value is non-null, clients must eventually call free(3) on it to
  avoid memory leaks.
*/
uint64_t *Hacl_Bignum4096_new_precompr2(uint32_t nLen, uint64_t *n)
{
  if (nLen == (uint32_t)0U || !(nLen <= (uint32_t)33554431U))
  {
    return NULL;
  }
  KRML_CHECK_SIZE(sizeof (uint64_t), nLen);
  uint64_t *res = KRML_HOST_CALLOC(nLen, sizeof (uint64_t));
  if (res == NULL)
  {
    return res;
  }
  uint64_t *res1 = res;
  uint64_t *res2 = res1;
  KRML_CHECK_SIZE(sizeof (uint64_t), nLen);
  uint64_t bn_zero[nLen];
  memset(bn_zero, 0U, nLen * sizeof (uint64_t));
  uint64_t mask = (uint64_t)0xFFFFFFFFFFFFFFFFU;
  for (uint32_t i = (uint32_t)0U; i < nLen; i++)
  {
    uint64_t uu____0 = FStar_UInt64_eq_mask(n[i], bn_zero[i]);
    mask = uu____0 & mask;
  }
  uint64_t mask10 = mask;
  uint64_t res3 = mask10;
  uint64_t mask0 = res3;
  uint32_t bits;
  if (mask0 == (uint64_t)0U)
  {
    uint32_t priv0 = (uint32_t)0U;
    for (uint32_t i = (uint32_t)0U; i < nLen; i++)
    {
      uint64_t mask1 = FStar_UInt64_eq_mask(n[i], (uint64_t)0U);
      uint32_t ite;
      if (mask1 == (uint64_t)0U)
      {
        ite = i;
      }
      else
      {
        ite = priv0;
      }
      priv0 = ite;
    }
    uint32_t ind = priv0;
    uint64_t uu____1 = n[ind];
    uint32_t priv = (uint32_t)0U;
    for (uint32_t i = (uint32_t)0U; i < (uint32_t)64U; i++)
    {
      uint64_t bit_i = uu____1 >> i & (uint64_t)1U;
      uint32_t ite;
      if (bit_i == (uint64_t)1U)
      {
        ite = i;
      }
      else
      {
        ite = priv;
      }
      priv = ite;
    }
    uint32_t bits0 = priv;
    bits = (uint32_t)64U * ind + bits0;
  }
  else
  {
    bits = (uint32_t)0U;
  }
  memset(res2, 0U, nLen * sizeof (uint64_t));
  Hacl_Bignum_bn_set_ith_bit(nLen, res2, bits);
  for (uint32_t i0 = (uint32_t)0U; i0 < (uint32_t)128U * nLen - bits; i0++)
  {
    uint64_t c0 = (uint64_t)0U;
    uint32_t k0 = nLen / (uint32_t)4U * (uint32_t)4U;
    for (uint32_t i = (uint32_t)0U; i < k0 / (uint32_t)4U; i++)
    {
      uint64_t t1 = res2[(uint32_t)4U * i];
      uint64_t t20 = res2[(uint32_t)4U * i];
      c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, t1, t20, res2 + (uint32_t)4U * i);
      uint64_t t10 = res2[(uint32_t)4U * i + (uint32_t)1U];
      uint64_t t21 = res2[(uint32_t)4U * i + (uint32_t)1U];
      c0 =
        Lib_IntTypes_Intrinsics_add_carry_u64(c0,
          t10,
          t21,
          res2 + (uint32_t)4U * i + (uint32_t)1U);
      uint64_t t11 = res2[(uint32_t)4U * i + (uint32_t)2U];
      uint64_t t22 = res2[(uint32_t)4U * i + (uint32_t)2U];
      c0 =
        Lib_IntTypes_Intrinsics_add_carry_u64(c0,
          t11,
          t22,
          res2 + (uint32_t)4U * i + (uint32_t)2U);
      uint64_t t12 = res2[(uint32_t)4U * i + (uint32_t)3U];
      uint64_t t2 = res2[(uint32_t)4U * i + (uint32_t)3U];
      c0 =
        Lib_IntTypes_Intrinsics_add_carry_u64(c0,
          t12,
          t2,
          res2 + (uint32_t)4U * i + (uint32_t)3U);
    }
    for (uint32_t i = k0; i < nLen; i++)
    {
      uint64_t t1 = res2[i];
      uint64_t t2 = res2[i];
      c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, t1, t2, res2 + i);
    }
    uint64_t c00 = c0;
    KRML_CHECK_SIZE(sizeof (uint64_t), nLen);
    uint64_t tmp[nLen];
    memset(tmp, 0U, nLen * sizeof (uint64_t));
    uint64_t c = (uint64_t)0U;
    uint32_t k = nLen / (uint32_t)4U * (uint32_t)4U;
    for (uint32_t i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
    {
      uint64_t t1 = res2[(uint32_t)4U * i];
      uint64_t t20 = n[(uint32_t)4U * i];
      c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t1, t20, tmp + (uint32_t)4U * i);
      uint64_t t10 = res2[(uint32_t)4U * i + (uint32_t)1U];
      uint64_t t21 = n[(uint32_t)4U * i + (uint32_t)1U];
      c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t10, t21, tmp + (uint32_t)4U * i + (uint32_t)1U);
      uint64_t t11 = res2[(uint32_t)4U * i + (uint32_t)2U];
      uint64_t t22 = n[(uint32_t)4U * i + (uint32_t)2U];
      c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t11, t22, tmp + (uint32_t)4U * i + (uint32_t)2U);
      uint64_t t12 = res2[(uint32_t)4U * i + (uint32_t)3U];
      uint64_t t2 = n[(uint32_t)4U * i + (uint32_t)3U];
      c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t12, t2, tmp + (uint32_t)4U * i + (uint32_t)3U);
    }
    for (uint32_t i = k; i < nLen; i++)
    {
      uint64_t t1 = res2[i];
      uint64_t t2 = n[i];
      c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t1, t2, tmp + i);
    }
    uint64_t c1 = c;
    uint64_t c2 = c00 - c1;
    for (uint32_t i = (uint32_t)0U; i < nLen; i++)
    {
      uint64_t *os = res2;
      uint64_t x = (c2 & res2[i]) | (~c2 & tmp[i]);
      os[i] = x;
    }
  }
  return res2;
}


/********************/
/* Loads and stores */
/********************/


/*
Load a bid-endian bignum from memory.

  The argument b points to len bytes of valid memory.
  The function returns a heap-allocated bignum of size sufficient to hold the
   result of loading b, or NULL if either the allocation failed, or the amount of
    required memory would exceed 4GB.

  If the return value is non-null, clients must eventually call free(3) on it to
  avoid memory leaks.
*/
uint64_t *Hacl_Bignum4096_new_bn_from_bytes_be(uint32_t len, uint8_t *b)
{
  if
  (
    len
    == (uint32_t)0U
    || !((len - (uint32_t)1U) / (uint32_t)8U + (uint32_t)1U <= (uint32_t)536870911U)
  )
  {
    return NULL;
  }
  KRML_CHECK_SIZE(sizeof (uint64_t), (len - (uint32_t)1U) / (uint32_t)8U + (uint32_t)1U);
  uint64_t
  *res = KRML_HOST_CALLOC((len - (uint32_t)1U) / (uint32_t)8U + (uint32_t)1U, sizeof (uint64_t));
  if (res == NULL)
  {
    return res;
  }
  uint64_t *res1 = res;
  uint64_t *res2 = res1;
  uint32_t bnLen = (len - (uint32_t)1U) / (uint32_t)8U + (uint32_t)1U;
  uint32_t tmpLen = (uint32_t)8U * bnLen;
  KRML_CHECK_SIZE(sizeof (uint8_t), tmpLen);
  uint8_t tmp[tmpLen];
  memset(tmp, 0U, tmpLen * sizeof (uint8_t));
  memcpy(tmp + tmpLen - len, b, len * sizeof (uint8_t));
  for (uint32_t i = (uint32_t)0U; i < bnLen; i++)
  {
    uint64_t *os = res2;
    uint64_t u = load64_be(tmp + (bnLen - i - (uint32_t)1U) * (uint32_t)8U);
    uint64_t x = u;
    os[i] = x;
  }
  return res2;
}

/*
Serialize a bignum into big-endian memory.

  The argument b points to a 4096-bit bignum.
  The outparam res points to 512 bytes of valid memory.
*/
void Hacl_Bignum4096_bn_to_bytes_be(uint64_t *b, uint8_t *res)
{
  uint32_t bnLen = ((uint32_t)512U - (uint32_t)1U) / (uint32_t)8U + (uint32_t)1U;
  uint32_t tmpLen = (uint32_t)8U * bnLen;
  KRML_CHECK_SIZE(sizeof (uint8_t), tmpLen);
  uint8_t tmp[tmpLen];
  memset(tmp, 0U, tmpLen * sizeof (uint8_t));
  for (uint32_t i = (uint32_t)0U; i < bnLen; i++)
  {
    store64_be(tmp + i * (uint32_t)8U, b[bnLen - i - (uint32_t)1U]);
  }
  memcpy(res, tmp + tmpLen - (uint32_t)512U, (uint32_t)512U * sizeof (uint8_t));
}


/***************/
/* Comparisons */
/***************/


uint64_t Hacl_Bignum4096_lt_mask(uint64_t *a, uint64_t *b)
{
  uint64_t acc = (uint64_t)0U;
  for (uint32_t i = (uint32_t)0U; i < (uint32_t)64U; i++)
  {
    uint64_t beq = FStar_UInt64_eq_mask(a[i], b[i]);
    uint64_t blt = ~FStar_UInt64_gte_mask(a[i], b[i]);
    acc = (beq & acc) | (~beq & ((blt & (uint64_t)0xFFFFFFFFFFFFFFFFU) | (~blt & (uint64_t)0U)));
  }
  return acc;
}
