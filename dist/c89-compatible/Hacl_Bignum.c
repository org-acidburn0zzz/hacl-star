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


#include "Hacl_Bignum.h"

inline void
Hacl_Bignum_Karatsuba_bn_karatsuba_mul_uint64(
  uint32_t aLen,
  uint64_t *a,
  uint64_t *b,
  uint64_t *tmp,
  uint64_t *res
)
{
  if (aLen < (uint32_t)32U || aLen % (uint32_t)2U == (uint32_t)1U)
  {
    uint32_t resLen = aLen + aLen;
    uint32_t i;
    memset(res, 0U, resLen * sizeof (uint64_t));
    for (i = (uint32_t)0U; i < aLen; i++)
    {
      uint64_t uu____0 = b[i];
      uint64_t *res_ = res + i;
      uint64_t c = (uint64_t)0U;
      uint32_t k = aLen / (uint32_t)4U * (uint32_t)4U;
      uint64_t r;
      {
        uint32_t i0;
        for (i0 = (uint32_t)0U; i0 < k / (uint32_t)4U; i0++)
        {
          uint64_t uu____1 = a[(uint32_t)4U * i0];
          uint64_t uu____2 = c;
          uint64_t *uu____3 = res_ + (uint32_t)4U * i0;
          FStar_UInt128_uint128 uu____4 = FStar_UInt128_uint64_to_uint128(uu____3[0U]);
          FStar_UInt128_uint128
          res1 =
            FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____1, uu____0),
                FStar_UInt128_uint64_to_uint128(uu____2)),
              uu____4);
          uu____3[0U] = FStar_UInt128_uint128_to_uint64(res1);
          c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res1, (uint32_t)64U));
          {
            uint64_t uu____5 = a[(uint32_t)4U * i0 + (uint32_t)1U];
            uint64_t uu____6 = c;
            uint64_t *uu____7 = res_ + (uint32_t)4U * i0 + (uint32_t)1U;
            FStar_UInt128_uint128 uu____8 = FStar_UInt128_uint64_to_uint128(uu____7[0U]);
            FStar_UInt128_uint128
            res10 =
              FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____5, uu____0),
                  FStar_UInt128_uint64_to_uint128(uu____6)),
                uu____8);
            uu____7[0U] = FStar_UInt128_uint128_to_uint64(res10);
            c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res10, (uint32_t)64U));
            {
              uint64_t uu____9 = a[(uint32_t)4U * i0 + (uint32_t)2U];
              uint64_t uu____10 = c;
              uint64_t *uu____11 = res_ + (uint32_t)4U * i0 + (uint32_t)2U;
              FStar_UInt128_uint128 uu____12 = FStar_UInt128_uint64_to_uint128(uu____11[0U]);
              FStar_UInt128_uint128
              res11 =
                FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____9, uu____0),
                    FStar_UInt128_uint64_to_uint128(uu____10)),
                  uu____12);
              uu____11[0U] = FStar_UInt128_uint128_to_uint64(res11);
              c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res11, (uint32_t)64U));
              {
                uint64_t uu____13 = a[(uint32_t)4U * i0 + (uint32_t)3U];
                uint64_t uu____14 = c;
                uint64_t *uu____15 = res_ + (uint32_t)4U * i0 + (uint32_t)3U;
                FStar_UInt128_uint128 uu____16 = FStar_UInt128_uint64_to_uint128(uu____15[0U]);
                FStar_UInt128_uint128
                res12 =
                  FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____13, uu____0),
                      FStar_UInt128_uint64_to_uint128(uu____14)),
                    uu____16);
                uu____15[0U] = FStar_UInt128_uint128_to_uint64(res12);
                c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res12, (uint32_t)64U));
              }
            }
          }
        }
      }
      {
        uint32_t i0;
        for (i0 = k; i0 < aLen; i0++)
        {
          uint64_t uu____17 = a[i0];
          uint64_t uu____18 = c;
          uint64_t *uu____19 = res_ + i0;
          FStar_UInt128_uint128 uu____20 = FStar_UInt128_uint64_to_uint128(uu____19[0U]);
          FStar_UInt128_uint128
          res1 =
            FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____17, uu____0),
                FStar_UInt128_uint64_to_uint128(uu____18)),
              uu____20);
          uu____19[0U] = FStar_UInt128_uint128_to_uint64(res1);
          c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res1, (uint32_t)64U));
        }
      }
      r = c;
      res[aLen + i] = r;
    }
    return;
  }
  {
    uint32_t len2 = aLen / (uint32_t)2U;
    uint64_t *a0 = a;
    uint64_t *a1 = a + len2;
    uint64_t *b0 = b;
    uint64_t *b1 = b + len2;
    uint64_t *t0 = tmp;
    uint64_t *t1 = tmp + len2;
    uint64_t *tmp_ = tmp + aLen;
    uint64_t c9 = (uint64_t)0U;
    uint32_t k0 = len2 / (uint32_t)4U * (uint32_t)4U;
    uint64_t c00;
    {
      uint32_t i;
      for (i = (uint32_t)0U; i < k0 / (uint32_t)4U; i++)
      {
        uint64_t t11 = a0[(uint32_t)4U * i];
        uint64_t t20 = a1[(uint32_t)4U * i];
        c9 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c9, t11, t20, tmp_ + (uint32_t)4U * i);
        {
          uint64_t t110 = a0[(uint32_t)4U * i + (uint32_t)1U];
          uint64_t t21 = a1[(uint32_t)4U * i + (uint32_t)1U];
          c9 =
            Lib_IntTypes_Intrinsics_sub_borrow_u64(c9,
              t110,
              t21,
              tmp_ + (uint32_t)4U * i + (uint32_t)1U);
          {
            uint64_t t111 = a0[(uint32_t)4U * i + (uint32_t)2U];
            uint64_t t22 = a1[(uint32_t)4U * i + (uint32_t)2U];
            c9 =
              Lib_IntTypes_Intrinsics_sub_borrow_u64(c9,
                t111,
                t22,
                tmp_ + (uint32_t)4U * i + (uint32_t)2U);
            {
              uint64_t t112 = a0[(uint32_t)4U * i + (uint32_t)3U];
              uint64_t t2 = a1[(uint32_t)4U * i + (uint32_t)3U];
              c9 =
                Lib_IntTypes_Intrinsics_sub_borrow_u64(c9,
                  t112,
                  t2,
                  tmp_ + (uint32_t)4U * i + (uint32_t)3U);
            }
          }
        }
      }
    }
    {
      uint32_t i;
      for (i = k0; i < len2; i++)
      {
        uint64_t t11 = a0[i];
        uint64_t t2 = a1[i];
        c9 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c9, t11, t2, tmp_ + i);
      }
    }
    c00 = c9;
    {
      uint64_t c10 = (uint64_t)0U;
      uint32_t k1 = len2 / (uint32_t)4U * (uint32_t)4U;
      uint64_t c11;
      uint64_t c0;
      {
        uint32_t i;
        for (i = (uint32_t)0U; i < k1 / (uint32_t)4U; i++)
        {
          uint64_t t11 = a1[(uint32_t)4U * i];
          uint64_t t20 = a0[(uint32_t)4U * i];
          c10 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c10, t11, t20, t0 + (uint32_t)4U * i);
          {
            uint64_t t110 = a1[(uint32_t)4U * i + (uint32_t)1U];
            uint64_t t21 = a0[(uint32_t)4U * i + (uint32_t)1U];
            c10 =
              Lib_IntTypes_Intrinsics_sub_borrow_u64(c10,
                t110,
                t21,
                t0 + (uint32_t)4U * i + (uint32_t)1U);
            {
              uint64_t t111 = a1[(uint32_t)4U * i + (uint32_t)2U];
              uint64_t t22 = a0[(uint32_t)4U * i + (uint32_t)2U];
              c10 =
                Lib_IntTypes_Intrinsics_sub_borrow_u64(c10,
                  t111,
                  t22,
                  t0 + (uint32_t)4U * i + (uint32_t)2U);
              {
                uint64_t t112 = a1[(uint32_t)4U * i + (uint32_t)3U];
                uint64_t t2 = a0[(uint32_t)4U * i + (uint32_t)3U];
                c10 =
                  Lib_IntTypes_Intrinsics_sub_borrow_u64(c10,
                    t112,
                    t2,
                    t0 + (uint32_t)4U * i + (uint32_t)3U);
              }
            }
          }
        }
      }
      {
        uint32_t i;
        for (i = k1; i < len2; i++)
        {
          uint64_t t11 = a1[i];
          uint64_t t2 = a0[i];
          c10 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c10, t11, t2, t0 + i);
        }
      }
      c11 = c10;
      {
        uint32_t i;
        for (i = (uint32_t)0U; i < len2; i++)
        {
          uint64_t *os = t0;
          uint64_t x = (((uint64_t)0U - c00) & t0[i]) | (~((uint64_t)0U - c00) & tmp_[i]);
          os[i] = x;
        }
      }
      c0 = c00;
      {
        uint64_t c12 = (uint64_t)0U;
        uint32_t k2 = len2 / (uint32_t)4U * (uint32_t)4U;
        uint64_t c010;
        {
          uint32_t i;
          for (i = (uint32_t)0U; i < k2 / (uint32_t)4U; i++)
          {
            uint64_t t11 = b0[(uint32_t)4U * i];
            uint64_t t20 = b1[(uint32_t)4U * i];
            c12 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c12, t11, t20, tmp_ + (uint32_t)4U * i);
            {
              uint64_t t110 = b0[(uint32_t)4U * i + (uint32_t)1U];
              uint64_t t21 = b1[(uint32_t)4U * i + (uint32_t)1U];
              c12 =
                Lib_IntTypes_Intrinsics_sub_borrow_u64(c12,
                  t110,
                  t21,
                  tmp_ + (uint32_t)4U * i + (uint32_t)1U);
              {
                uint64_t t111 = b0[(uint32_t)4U * i + (uint32_t)2U];
                uint64_t t22 = b1[(uint32_t)4U * i + (uint32_t)2U];
                c12 =
                  Lib_IntTypes_Intrinsics_sub_borrow_u64(c12,
                    t111,
                    t22,
                    tmp_ + (uint32_t)4U * i + (uint32_t)2U);
                {
                  uint64_t t112 = b0[(uint32_t)4U * i + (uint32_t)3U];
                  uint64_t t2 = b1[(uint32_t)4U * i + (uint32_t)3U];
                  c12 =
                    Lib_IntTypes_Intrinsics_sub_borrow_u64(c12,
                      t112,
                      t2,
                      tmp_ + (uint32_t)4U * i + (uint32_t)3U);
                }
              }
            }
          }
        }
        {
          uint32_t i;
          for (i = k2; i < len2; i++)
          {
            uint64_t t11 = b0[i];
            uint64_t t2 = b1[i];
            c12 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c12, t11, t2, tmp_ + i);
          }
        }
        c010 = c12;
        {
          uint64_t c13 = (uint64_t)0U;
          uint32_t k3 = len2 / (uint32_t)4U * (uint32_t)4U;
          uint64_t c14;
          uint64_t c1;
          uint64_t *t23;
          uint64_t *tmp1;
          uint64_t *r01;
          uint64_t *r23;
          uint64_t *r011;
          uint64_t *r231;
          uint64_t *t01;
          uint64_t *t231;
          uint64_t *t45;
          uint64_t *t67;
          {
            uint32_t i;
            for (i = (uint32_t)0U; i < k3 / (uint32_t)4U; i++)
            {
              uint64_t t11 = b1[(uint32_t)4U * i];
              uint64_t t20 = b0[(uint32_t)4U * i];
              c13 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c13, t11, t20, t1 + (uint32_t)4U * i);
              {
                uint64_t t110 = b1[(uint32_t)4U * i + (uint32_t)1U];
                uint64_t t21 = b0[(uint32_t)4U * i + (uint32_t)1U];
                c13 =
                  Lib_IntTypes_Intrinsics_sub_borrow_u64(c13,
                    t110,
                    t21,
                    t1 + (uint32_t)4U * i + (uint32_t)1U);
                {
                  uint64_t t111 = b1[(uint32_t)4U * i + (uint32_t)2U];
                  uint64_t t22 = b0[(uint32_t)4U * i + (uint32_t)2U];
                  c13 =
                    Lib_IntTypes_Intrinsics_sub_borrow_u64(c13,
                      t111,
                      t22,
                      t1 + (uint32_t)4U * i + (uint32_t)2U);
                  {
                    uint64_t t112 = b1[(uint32_t)4U * i + (uint32_t)3U];
                    uint64_t t2 = b0[(uint32_t)4U * i + (uint32_t)3U];
                    c13 =
                      Lib_IntTypes_Intrinsics_sub_borrow_u64(c13,
                        t112,
                        t2,
                        t1 + (uint32_t)4U * i + (uint32_t)3U);
                  }
                }
              }
            }
          }
          {
            uint32_t i;
            for (i = k3; i < len2; i++)
            {
              uint64_t t11 = b1[i];
              uint64_t t2 = b0[i];
              c13 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c13, t11, t2, t1 + i);
            }
          }
          c14 = c13;
          {
            uint32_t i;
            for (i = (uint32_t)0U; i < len2; i++)
            {
              uint64_t *os = t1;
              uint64_t x = (((uint64_t)0U - c010) & t1[i]) | (~((uint64_t)0U - c010) & tmp_[i]);
              os[i] = x;
            }
          }
          c1 = c010;
          t23 = tmp + aLen;
          tmp1 = tmp + aLen + aLen;
          Hacl_Bignum_Karatsuba_bn_karatsuba_mul_uint64(len2, t0, t1, tmp1, t23);
          r01 = res;
          r23 = res + aLen;
          Hacl_Bignum_Karatsuba_bn_karatsuba_mul_uint64(len2, a0, b0, tmp1, r01);
          Hacl_Bignum_Karatsuba_bn_karatsuba_mul_uint64(len2, a1, b1, tmp1, r23);
          r011 = res;
          r231 = res + aLen;
          t01 = tmp;
          t231 = tmp + aLen;
          t45 = tmp + (uint32_t)2U * aLen;
          t67 = tmp + (uint32_t)3U * aLen;
          {
            uint64_t c15 = (uint64_t)0U;
            uint32_t k4 = aLen / (uint32_t)4U * (uint32_t)4U;
            uint64_t c2;
            uint64_t c_sign;
            {
              uint32_t i;
              for (i = (uint32_t)0U; i < k4 / (uint32_t)4U; i++)
              {
                uint64_t t11 = r011[(uint32_t)4U * i];
                uint64_t t20 = r231[(uint32_t)4U * i];
                c15 = Lib_IntTypes_Intrinsics_add_carry_u64(c15, t11, t20, t01 + (uint32_t)4U * i);
                {
                  uint64_t t110 = r011[(uint32_t)4U * i + (uint32_t)1U];
                  uint64_t t21 = r231[(uint32_t)4U * i + (uint32_t)1U];
                  c15 =
                    Lib_IntTypes_Intrinsics_add_carry_u64(c15,
                      t110,
                      t21,
                      t01 + (uint32_t)4U * i + (uint32_t)1U);
                  {
                    uint64_t t111 = r011[(uint32_t)4U * i + (uint32_t)2U];
                    uint64_t t22 = r231[(uint32_t)4U * i + (uint32_t)2U];
                    c15 =
                      Lib_IntTypes_Intrinsics_add_carry_u64(c15,
                        t111,
                        t22,
                        t01 + (uint32_t)4U * i + (uint32_t)2U);
                    {
                      uint64_t t112 = r011[(uint32_t)4U * i + (uint32_t)3U];
                      uint64_t t2 = r231[(uint32_t)4U * i + (uint32_t)3U];
                      c15 =
                        Lib_IntTypes_Intrinsics_add_carry_u64(c15,
                          t112,
                          t2,
                          t01 + (uint32_t)4U * i + (uint32_t)3U);
                    }
                  }
                }
              }
            }
            {
              uint32_t i;
              for (i = k4; i < aLen; i++)
              {
                uint64_t t11 = r011[i];
                uint64_t t2 = r231[i];
                c15 = Lib_IntTypes_Intrinsics_add_carry_u64(c15, t11, t2, t01 + i);
              }
            }
            c2 = c15;
            c_sign = c0 ^ c1;
            {
              uint64_t c16 = (uint64_t)0U;
              uint32_t k5 = aLen / (uint32_t)4U * (uint32_t)4U;
              uint64_t c3;
              uint64_t c31;
              {
                uint32_t i;
                for (i = (uint32_t)0U; i < k5 / (uint32_t)4U; i++)
                {
                  uint64_t t11 = t01[(uint32_t)4U * i];
                  uint64_t t20 = t231[(uint32_t)4U * i];
                  c16 =
                    Lib_IntTypes_Intrinsics_sub_borrow_u64(c16,
                      t11,
                      t20,
                      t67 + (uint32_t)4U * i);
                  {
                    uint64_t t110 = t01[(uint32_t)4U * i + (uint32_t)1U];
                    uint64_t t21 = t231[(uint32_t)4U * i + (uint32_t)1U];
                    c16 =
                      Lib_IntTypes_Intrinsics_sub_borrow_u64(c16,
                        t110,
                        t21,
                        t67 + (uint32_t)4U * i + (uint32_t)1U);
                    {
                      uint64_t t111 = t01[(uint32_t)4U * i + (uint32_t)2U];
                      uint64_t t22 = t231[(uint32_t)4U * i + (uint32_t)2U];
                      c16 =
                        Lib_IntTypes_Intrinsics_sub_borrow_u64(c16,
                          t111,
                          t22,
                          t67 + (uint32_t)4U * i + (uint32_t)2U);
                      {
                        uint64_t t112 = t01[(uint32_t)4U * i + (uint32_t)3U];
                        uint64_t t2 = t231[(uint32_t)4U * i + (uint32_t)3U];
                        c16 =
                          Lib_IntTypes_Intrinsics_sub_borrow_u64(c16,
                            t112,
                            t2,
                            t67 + (uint32_t)4U * i + (uint32_t)3U);
                      }
                    }
                  }
                }
              }
              {
                uint32_t i;
                for (i = k5; i < aLen; i++)
                {
                  uint64_t t11 = t01[i];
                  uint64_t t2 = t231[i];
                  c16 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c16, t11, t2, t67 + i);
                }
              }
              c3 = c16;
              c31 = c2 - c3;
              {
                uint64_t c17 = (uint64_t)0U;
                uint32_t k6 = aLen / (uint32_t)4U * (uint32_t)4U;
                uint64_t c4;
                uint64_t c41;
                uint64_t mask;
                uint64_t c5;
                {
                  uint32_t i;
                  for (i = (uint32_t)0U; i < k6 / (uint32_t)4U; i++)
                  {
                    uint64_t t11 = t01[(uint32_t)4U * i];
                    uint64_t t20 = t231[(uint32_t)4U * i];
                    c17 =
                      Lib_IntTypes_Intrinsics_add_carry_u64(c17,
                        t11,
                        t20,
                        t45 + (uint32_t)4U * i);
                    {
                      uint64_t t110 = t01[(uint32_t)4U * i + (uint32_t)1U];
                      uint64_t t21 = t231[(uint32_t)4U * i + (uint32_t)1U];
                      c17 =
                        Lib_IntTypes_Intrinsics_add_carry_u64(c17,
                          t110,
                          t21,
                          t45 + (uint32_t)4U * i + (uint32_t)1U);
                      {
                        uint64_t t111 = t01[(uint32_t)4U * i + (uint32_t)2U];
                        uint64_t t22 = t231[(uint32_t)4U * i + (uint32_t)2U];
                        c17 =
                          Lib_IntTypes_Intrinsics_add_carry_u64(c17,
                            t111,
                            t22,
                            t45 + (uint32_t)4U * i + (uint32_t)2U);
                        {
                          uint64_t t112 = t01[(uint32_t)4U * i + (uint32_t)3U];
                          uint64_t t2 = t231[(uint32_t)4U * i + (uint32_t)3U];
                          c17 =
                            Lib_IntTypes_Intrinsics_add_carry_u64(c17,
                              t112,
                              t2,
                              t45 + (uint32_t)4U * i + (uint32_t)3U);
                        }
                      }
                    }
                  }
                }
                {
                  uint32_t i;
                  for (i = k6; i < aLen; i++)
                  {
                    uint64_t t11 = t01[i];
                    uint64_t t2 = t231[i];
                    c17 = Lib_IntTypes_Intrinsics_add_carry_u64(c17, t11, t2, t45 + i);
                  }
                }
                c4 = c17;
                c41 = c2 + c4;
                mask = (uint64_t)0U - c_sign;
                {
                  uint32_t i;
                  for (i = (uint32_t)0U; i < aLen; i++)
                  {
                    uint64_t *os = t45;
                    uint64_t x = (mask & t45[i]) | (~mask & t67[i]);
                    os[i] = x;
                  }
                }
                c5 = (mask & c41) | (~mask & c31);
                {
                  uint32_t aLen2 = aLen / (uint32_t)2U;
                  uint64_t *r0 = res + aLen2;
                  uint64_t c18 = (uint64_t)0U;
                  uint32_t k7 = aLen / (uint32_t)4U * (uint32_t)4U;
                  uint64_t r10;
                  uint64_t c6;
                  uint64_t c7;
                  {
                    uint32_t i;
                    for (i = (uint32_t)0U; i < k7 / (uint32_t)4U; i++)
                    {
                      uint64_t t11 = r0[(uint32_t)4U * i];
                      uint64_t t20 = t45[(uint32_t)4U * i];
                      c18 =
                        Lib_IntTypes_Intrinsics_add_carry_u64(c18,
                          t11,
                          t20,
                          r0 + (uint32_t)4U * i);
                      {
                        uint64_t t110 = r0[(uint32_t)4U * i + (uint32_t)1U];
                        uint64_t t21 = t45[(uint32_t)4U * i + (uint32_t)1U];
                        c18 =
                          Lib_IntTypes_Intrinsics_add_carry_u64(c18,
                            t110,
                            t21,
                            r0 + (uint32_t)4U * i + (uint32_t)1U);
                        {
                          uint64_t t111 = r0[(uint32_t)4U * i + (uint32_t)2U];
                          uint64_t t22 = t45[(uint32_t)4U * i + (uint32_t)2U];
                          c18 =
                            Lib_IntTypes_Intrinsics_add_carry_u64(c18,
                              t111,
                              t22,
                              r0 + (uint32_t)4U * i + (uint32_t)2U);
                          {
                            uint64_t t112 = r0[(uint32_t)4U * i + (uint32_t)3U];
                            uint64_t t2 = t45[(uint32_t)4U * i + (uint32_t)3U];
                            c18 =
                              Lib_IntTypes_Intrinsics_add_carry_u64(c18,
                                t112,
                                t2,
                                r0 + (uint32_t)4U * i + (uint32_t)3U);
                          }
                        }
                      }
                    }
                  }
                  {
                    uint32_t i;
                    for (i = k7; i < aLen; i++)
                    {
                      uint64_t t11 = r0[i];
                      uint64_t t2 = t45[i];
                      c18 = Lib_IntTypes_Intrinsics_add_carry_u64(c18, t11, t2, r0 + i);
                    }
                  }
                  r10 = c18;
                  c6 = r10;
                  c7 = c5 + c6;
                  {
                    uint64_t c71 = c7;
                    uint64_t *r = res + aLen + aLen2;
                    uint64_t *a01 = r;
                    uint64_t *res0 = r;
                    uint64_t c19 = (uint64_t)0U;
                    uint32_t k8 = (uint32_t)0U;
                    uint64_t c01;
                    uint64_t r1;
                    uint64_t c8;
                    uint64_t c20;
                    uint64_t c21;
                    {
                      uint32_t i;
                      for (i = (uint32_t)0U; i < k8 / (uint32_t)4U; i++)
                      {
                        uint64_t t11 = a01[(uint32_t)4U * i];
                        uint64_t t20 = (&c71)[(uint32_t)4U * i];
                        c19 =
                          Lib_IntTypes_Intrinsics_add_carry_u64(c19,
                            t11,
                            t20,
                            res0 + (uint32_t)4U * i);
                        {
                          uint64_t t110 = a01[(uint32_t)4U * i + (uint32_t)1U];
                          uint64_t t21 = (&c71)[(uint32_t)4U * i + (uint32_t)1U];
                          c19 =
                            Lib_IntTypes_Intrinsics_add_carry_u64(c19,
                              t110,
                              t21,
                              res0 + (uint32_t)4U * i + (uint32_t)1U);
                          {
                            uint64_t t111 = a01[(uint32_t)4U * i + (uint32_t)2U];
                            uint64_t t22 = (&c71)[(uint32_t)4U * i + (uint32_t)2U];
                            c19 =
                              Lib_IntTypes_Intrinsics_add_carry_u64(c19,
                                t111,
                                t22,
                                res0 + (uint32_t)4U * i + (uint32_t)2U);
                            {
                              uint64_t t112 = a01[(uint32_t)4U * i + (uint32_t)3U];
                              uint64_t t2 = (&c71)[(uint32_t)4U * i + (uint32_t)3U];
                              c19 =
                                Lib_IntTypes_Intrinsics_add_carry_u64(c19,
                                  t112,
                                  t2,
                                  res0 + (uint32_t)4U * i + (uint32_t)3U);
                            }
                          }
                        }
                      }
                    }
                    {
                      uint32_t i;
                      for (i = k8; i < (uint32_t)1U; i++)
                      {
                        uint64_t t11 = a01[i];
                        uint64_t t2 = (&c71)[i];
                        c19 = Lib_IntTypes_Intrinsics_add_carry_u64(c19, t11, t2, res0 + i);
                      }
                    }
                    c01 = c19;
                    if ((uint32_t)1U < aLen + aLen - (aLen + aLen2))
                    {
                      uint32_t rLen = aLen + aLen - (aLen + aLen2) - (uint32_t)1U;
                      uint64_t *a11 = r + (uint32_t)1U;
                      uint64_t *res1 = r + (uint32_t)1U;
                      uint64_t c = c01;
                      uint32_t k = rLen / (uint32_t)4U * (uint32_t)4U;
                      {
                        uint32_t i;
                        for (i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
                        {
                          uint64_t t11 = a11[(uint32_t)4U * i];
                          c =
                            Lib_IntTypes_Intrinsics_add_carry_u64(c,
                              t11,
                              (uint64_t)0U,
                              res1 + (uint32_t)4U * i);
                          {
                            uint64_t t110 = a11[(uint32_t)4U * i + (uint32_t)1U];
                            c =
                              Lib_IntTypes_Intrinsics_add_carry_u64(c,
                                t110,
                                (uint64_t)0U,
                                res1 + (uint32_t)4U * i + (uint32_t)1U);
                            {
                              uint64_t t111 = a11[(uint32_t)4U * i + (uint32_t)2U];
                              c =
                                Lib_IntTypes_Intrinsics_add_carry_u64(c,
                                  t111,
                                  (uint64_t)0U,
                                  res1 + (uint32_t)4U * i + (uint32_t)2U);
                              {
                                uint64_t t112 = a11[(uint32_t)4U * i + (uint32_t)3U];
                                c =
                                  Lib_IntTypes_Intrinsics_add_carry_u64(c,
                                    t112,
                                    (uint64_t)0U,
                                    res1 + (uint32_t)4U * i + (uint32_t)3U);
                              }
                            }
                          }
                        }
                      }
                      {
                        uint32_t i;
                        for (i = k; i < rLen; i++)
                        {
                          uint64_t t11 = a11[i];
                          c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t11, (uint64_t)0U, res1 + i);
                        }
                      }
                      {
                        uint64_t c110 = c;
                        r1 = c110;
                      }
                    }
                    else
                    {
                      r1 = c01;
                    }
                    c8 = r1;
                    c20 = c8;
                    c21 = c20;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

inline void
Hacl_Bignum_Karatsuba_bn_karatsuba_sqr_uint64(
  uint32_t aLen,
  uint64_t *a,
  uint64_t *tmp,
  uint64_t *res
)
{
  if (aLen < (uint32_t)32U || aLen % (uint32_t)2U == (uint32_t)1U)
  {
    uint32_t resLen = aLen + aLen;
    memset(res, 0U, resLen * sizeof (uint64_t));
    {
      uint32_t i0;
      for (i0 = (uint32_t)0U; i0 < aLen; i0++)
      {
        uint64_t *uu____0 = a;
        uint64_t uu____1 = a[i0];
        uint64_t *res_ = res + i0;
        uint64_t c = (uint64_t)0U;
        uint32_t k = i0 / (uint32_t)4U * (uint32_t)4U;
        {
          uint32_t i;
          for (i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
          {
            uint64_t uu____2 = uu____0[(uint32_t)4U * i];
            uint64_t uu____3 = c;
            uint64_t *uu____4 = res_ + (uint32_t)4U * i;
            FStar_UInt128_uint128 uu____5 = FStar_UInt128_uint64_to_uint128(uu____4[0U]);
            FStar_UInt128_uint128
            res1 =
              FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____2, uu____1),
                  FStar_UInt128_uint64_to_uint128(uu____3)),
                uu____5);
            uu____4[0U] = FStar_UInt128_uint128_to_uint64(res1);
            c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res1, (uint32_t)64U));
            {
              uint64_t uu____6 = uu____0[(uint32_t)4U * i + (uint32_t)1U];
              uint64_t uu____7 = c;
              uint64_t *uu____8 = res_ + (uint32_t)4U * i + (uint32_t)1U;
              FStar_UInt128_uint128 uu____9 = FStar_UInt128_uint64_to_uint128(uu____8[0U]);
              FStar_UInt128_uint128
              res10 =
                FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____6, uu____1),
                    FStar_UInt128_uint64_to_uint128(uu____7)),
                  uu____9);
              uu____8[0U] = FStar_UInt128_uint128_to_uint64(res10);
              c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res10, (uint32_t)64U));
              {
                uint64_t uu____10 = uu____0[(uint32_t)4U * i + (uint32_t)2U];
                uint64_t uu____11 = c;
                uint64_t *uu____12 = res_ + (uint32_t)4U * i + (uint32_t)2U;
                FStar_UInt128_uint128 uu____13 = FStar_UInt128_uint64_to_uint128(uu____12[0U]);
                FStar_UInt128_uint128
                res11 =
                  FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____10, uu____1),
                      FStar_UInt128_uint64_to_uint128(uu____11)),
                    uu____13);
                uu____12[0U] = FStar_UInt128_uint128_to_uint64(res11);
                c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res11, (uint32_t)64U));
                {
                  uint64_t uu____14 = uu____0[(uint32_t)4U * i + (uint32_t)3U];
                  uint64_t uu____15 = c;
                  uint64_t *uu____16 = res_ + (uint32_t)4U * i + (uint32_t)3U;
                  FStar_UInt128_uint128 uu____17 = FStar_UInt128_uint64_to_uint128(uu____16[0U]);
                  FStar_UInt128_uint128
                  res12 =
                    FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____14, uu____1),
                        FStar_UInt128_uint64_to_uint128(uu____15)),
                      uu____17);
                  uu____16[0U] = FStar_UInt128_uint128_to_uint64(res12);
                  c =
                    FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res12, (uint32_t)64U));
                }
              }
            }
          }
        }
        {
          uint32_t i;
          for (i = k; i < i0; i++)
          {
            uint64_t uu____18 = uu____0[i];
            uint64_t uu____19 = c;
            uint64_t *uu____20 = res_ + i;
            FStar_UInt128_uint128 uu____21 = FStar_UInt128_uint64_to_uint128(uu____20[0U]);
            FStar_UInt128_uint128
            res1 =
              FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____18, uu____1),
                  FStar_UInt128_uint64_to_uint128(uu____19)),
                uu____21);
            uu____20[0U] = FStar_UInt128_uint128_to_uint64(res1);
            c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res1, (uint32_t)64U));
          }
        }
        {
          uint64_t r = c;
          res[i0 + i0] = r;
        }
      }
    }
    {
      uint64_t c0 = (uint64_t)0U;
      uint32_t k0 = resLen / (uint32_t)4U * (uint32_t)4U;
      uint64_t uu____22;
      {
        uint32_t i;
        for (i = (uint32_t)0U; i < k0 / (uint32_t)4U; i++)
        {
          uint64_t t1 = res[(uint32_t)4U * i];
          uint64_t t20 = res[(uint32_t)4U * i];
          c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, t1, t20, res + (uint32_t)4U * i);
          {
            uint64_t t10 = res[(uint32_t)4U * i + (uint32_t)1U];
            uint64_t t21 = res[(uint32_t)4U * i + (uint32_t)1U];
            c0 =
              Lib_IntTypes_Intrinsics_add_carry_u64(c0,
                t10,
                t21,
                res + (uint32_t)4U * i + (uint32_t)1U);
            {
              uint64_t t11 = res[(uint32_t)4U * i + (uint32_t)2U];
              uint64_t t22 = res[(uint32_t)4U * i + (uint32_t)2U];
              c0 =
                Lib_IntTypes_Intrinsics_add_carry_u64(c0,
                  t11,
                  t22,
                  res + (uint32_t)4U * i + (uint32_t)2U);
              {
                uint64_t t12 = res[(uint32_t)4U * i + (uint32_t)3U];
                uint64_t t2 = res[(uint32_t)4U * i + (uint32_t)3U];
                c0 =
                  Lib_IntTypes_Intrinsics_add_carry_u64(c0,
                    t12,
                    t2,
                    res + (uint32_t)4U * i + (uint32_t)3U);
              }
            }
          }
        }
      }
      {
        uint32_t i;
        for (i = k0; i < resLen; i++)
        {
          uint64_t t1 = res[i];
          uint64_t t2 = res[i];
          c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, t1, t2, res + i);
        }
      }
      uu____22 = c0;
      KRML_CHECK_SIZE(sizeof (uint64_t), resLen);
      {
        uint64_t tmp1[resLen];
        memset(tmp1, 0U, resLen * sizeof (uint64_t));
        {
          uint32_t i;
          for (i = (uint32_t)0U; i < aLen; i++)
          {
            FStar_UInt128_uint128 res1 = FStar_UInt128_mul_wide(a[i], a[i]);
            uint64_t
            hi = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res1, (uint32_t)64U));
            uint64_t lo = FStar_UInt128_uint128_to_uint64(res1);
            tmp1[(uint32_t)2U * i] = lo;
            tmp1[(uint32_t)2U * i + (uint32_t)1U] = hi;
          }
        }
        {
          uint64_t c = (uint64_t)0U;
          uint32_t k = resLen / (uint32_t)4U * (uint32_t)4U;
          uint64_t uu____23;
          {
            uint32_t i;
            for (i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
            {
              uint64_t t1 = res[(uint32_t)4U * i];
              uint64_t t20 = tmp1[(uint32_t)4U * i];
              c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t1, t20, res + (uint32_t)4U * i);
              {
                uint64_t t10 = res[(uint32_t)4U * i + (uint32_t)1U];
                uint64_t t21 = tmp1[(uint32_t)4U * i + (uint32_t)1U];
                c =
                  Lib_IntTypes_Intrinsics_add_carry_u64(c,
                    t10,
                    t21,
                    res + (uint32_t)4U * i + (uint32_t)1U);
                {
                  uint64_t t11 = res[(uint32_t)4U * i + (uint32_t)2U];
                  uint64_t t22 = tmp1[(uint32_t)4U * i + (uint32_t)2U];
                  c =
                    Lib_IntTypes_Intrinsics_add_carry_u64(c,
                      t11,
                      t22,
                      res + (uint32_t)4U * i + (uint32_t)2U);
                  {
                    uint64_t t12 = res[(uint32_t)4U * i + (uint32_t)3U];
                    uint64_t t2 = tmp1[(uint32_t)4U * i + (uint32_t)3U];
                    c =
                      Lib_IntTypes_Intrinsics_add_carry_u64(c,
                        t12,
                        t2,
                        res + (uint32_t)4U * i + (uint32_t)3U);
                  }
                }
              }
            }
          }
          {
            uint32_t i;
            for (i = k; i < resLen; i++)
            {
              uint64_t t1 = res[i];
              uint64_t t2 = tmp1[i];
              c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t1, t2, res + i);
            }
          }
          uu____23 = c;
          return;
        }
      }
    }
  }
  {
    uint32_t len2 = aLen / (uint32_t)2U;
    uint64_t *a0 = a;
    uint64_t *a1 = a + len2;
    uint64_t *t0 = tmp;
    uint64_t *tmp_ = tmp + aLen;
    uint64_t c4 = (uint64_t)0U;
    uint32_t k0 = len2 / (uint32_t)4U * (uint32_t)4U;
    uint64_t c00;
    {
      uint32_t i;
      for (i = (uint32_t)0U; i < k0 / (uint32_t)4U; i++)
      {
        uint64_t t1 = a0[(uint32_t)4U * i];
        uint64_t t20 = a1[(uint32_t)4U * i];
        c4 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c4, t1, t20, tmp_ + (uint32_t)4U * i);
        {
          uint64_t t10 = a0[(uint32_t)4U * i + (uint32_t)1U];
          uint64_t t21 = a1[(uint32_t)4U * i + (uint32_t)1U];
          c4 =
            Lib_IntTypes_Intrinsics_sub_borrow_u64(c4,
              t10,
              t21,
              tmp_ + (uint32_t)4U * i + (uint32_t)1U);
          {
            uint64_t t11 = a0[(uint32_t)4U * i + (uint32_t)2U];
            uint64_t t22 = a1[(uint32_t)4U * i + (uint32_t)2U];
            c4 =
              Lib_IntTypes_Intrinsics_sub_borrow_u64(c4,
                t11,
                t22,
                tmp_ + (uint32_t)4U * i + (uint32_t)2U);
            {
              uint64_t t12 = a0[(uint32_t)4U * i + (uint32_t)3U];
              uint64_t t2 = a1[(uint32_t)4U * i + (uint32_t)3U];
              c4 =
                Lib_IntTypes_Intrinsics_sub_borrow_u64(c4,
                  t12,
                  t2,
                  tmp_ + (uint32_t)4U * i + (uint32_t)3U);
            }
          }
        }
      }
    }
    {
      uint32_t i;
      for (i = k0; i < len2; i++)
      {
        uint64_t t1 = a0[i];
        uint64_t t2 = a1[i];
        c4 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c4, t1, t2, tmp_ + i);
      }
    }
    c00 = c4;
    {
      uint64_t c9 = (uint64_t)0U;
      uint32_t k1 = len2 / (uint32_t)4U * (uint32_t)4U;
      uint64_t c1;
      uint64_t c0;
      uint64_t *t23;
      uint64_t *tmp1;
      uint64_t *r01;
      uint64_t *r23;
      uint64_t *r011;
      uint64_t *r231;
      uint64_t *t01;
      uint64_t *t231;
      uint64_t *t45;
      {
        uint32_t i;
        for (i = (uint32_t)0U; i < k1 / (uint32_t)4U; i++)
        {
          uint64_t t1 = a1[(uint32_t)4U * i];
          uint64_t t20 = a0[(uint32_t)4U * i];
          c9 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c9, t1, t20, t0 + (uint32_t)4U * i);
          {
            uint64_t t10 = a1[(uint32_t)4U * i + (uint32_t)1U];
            uint64_t t21 = a0[(uint32_t)4U * i + (uint32_t)1U];
            c9 =
              Lib_IntTypes_Intrinsics_sub_borrow_u64(c9,
                t10,
                t21,
                t0 + (uint32_t)4U * i + (uint32_t)1U);
            {
              uint64_t t11 = a1[(uint32_t)4U * i + (uint32_t)2U];
              uint64_t t22 = a0[(uint32_t)4U * i + (uint32_t)2U];
              c9 =
                Lib_IntTypes_Intrinsics_sub_borrow_u64(c9,
                  t11,
                  t22,
                  t0 + (uint32_t)4U * i + (uint32_t)2U);
              {
                uint64_t t12 = a1[(uint32_t)4U * i + (uint32_t)3U];
                uint64_t t2 = a0[(uint32_t)4U * i + (uint32_t)3U];
                c9 =
                  Lib_IntTypes_Intrinsics_sub_borrow_u64(c9,
                    t12,
                    t2,
                    t0 + (uint32_t)4U * i + (uint32_t)3U);
              }
            }
          }
        }
      }
      {
        uint32_t i;
        for (i = k1; i < len2; i++)
        {
          uint64_t t1 = a1[i];
          uint64_t t2 = a0[i];
          c9 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c9, t1, t2, t0 + i);
        }
      }
      c1 = c9;
      {
        uint32_t i;
        for (i = (uint32_t)0U; i < len2; i++)
        {
          uint64_t *os = t0;
          uint64_t x = (((uint64_t)0U - c00) & t0[i]) | (~((uint64_t)0U - c00) & tmp_[i]);
          os[i] = x;
        }
      }
      c0 = c00;
      t23 = tmp + aLen;
      tmp1 = tmp + aLen + aLen;
      Hacl_Bignum_Karatsuba_bn_karatsuba_sqr_uint64(len2, t0, tmp1, t23);
      r01 = res;
      r23 = res + aLen;
      Hacl_Bignum_Karatsuba_bn_karatsuba_sqr_uint64(len2, a0, tmp1, r01);
      Hacl_Bignum_Karatsuba_bn_karatsuba_sqr_uint64(len2, a1, tmp1, r23);
      r011 = res;
      r231 = res + aLen;
      t01 = tmp;
      t231 = tmp + aLen;
      t45 = tmp + (uint32_t)2U * aLen;
      {
        uint64_t c10 = (uint64_t)0U;
        uint32_t k2 = aLen / (uint32_t)4U * (uint32_t)4U;
        uint64_t c2;
        {
          uint32_t i;
          for (i = (uint32_t)0U; i < k2 / (uint32_t)4U; i++)
          {
            uint64_t t1 = r011[(uint32_t)4U * i];
            uint64_t t20 = r231[(uint32_t)4U * i];
            c10 = Lib_IntTypes_Intrinsics_add_carry_u64(c10, t1, t20, t01 + (uint32_t)4U * i);
            {
              uint64_t t10 = r011[(uint32_t)4U * i + (uint32_t)1U];
              uint64_t t21 = r231[(uint32_t)4U * i + (uint32_t)1U];
              c10 =
                Lib_IntTypes_Intrinsics_add_carry_u64(c10,
                  t10,
                  t21,
                  t01 + (uint32_t)4U * i + (uint32_t)1U);
              {
                uint64_t t11 = r011[(uint32_t)4U * i + (uint32_t)2U];
                uint64_t t22 = r231[(uint32_t)4U * i + (uint32_t)2U];
                c10 =
                  Lib_IntTypes_Intrinsics_add_carry_u64(c10,
                    t11,
                    t22,
                    t01 + (uint32_t)4U * i + (uint32_t)2U);
                {
                  uint64_t t12 = r011[(uint32_t)4U * i + (uint32_t)3U];
                  uint64_t t2 = r231[(uint32_t)4U * i + (uint32_t)3U];
                  c10 =
                    Lib_IntTypes_Intrinsics_add_carry_u64(c10,
                      t12,
                      t2,
                      t01 + (uint32_t)4U * i + (uint32_t)3U);
                }
              }
            }
          }
        }
        {
          uint32_t i;
          for (i = k2; i < aLen; i++)
          {
            uint64_t t1 = r011[i];
            uint64_t t2 = r231[i];
            c10 = Lib_IntTypes_Intrinsics_add_carry_u64(c10, t1, t2, t01 + i);
          }
        }
        c2 = c10;
        {
          uint64_t c11 = (uint64_t)0U;
          uint32_t k3 = aLen / (uint32_t)4U * (uint32_t)4U;
          uint64_t c3;
          uint64_t c5;
          {
            uint32_t i;
            for (i = (uint32_t)0U; i < k3 / (uint32_t)4U; i++)
            {
              uint64_t t1 = t01[(uint32_t)4U * i];
              uint64_t t20 = t231[(uint32_t)4U * i];
              c11 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c11, t1, t20, t45 + (uint32_t)4U * i);
              {
                uint64_t t10 = t01[(uint32_t)4U * i + (uint32_t)1U];
                uint64_t t21 = t231[(uint32_t)4U * i + (uint32_t)1U];
                c11 =
                  Lib_IntTypes_Intrinsics_sub_borrow_u64(c11,
                    t10,
                    t21,
                    t45 + (uint32_t)4U * i + (uint32_t)1U);
                {
                  uint64_t t11 = t01[(uint32_t)4U * i + (uint32_t)2U];
                  uint64_t t22 = t231[(uint32_t)4U * i + (uint32_t)2U];
                  c11 =
                    Lib_IntTypes_Intrinsics_sub_borrow_u64(c11,
                      t11,
                      t22,
                      t45 + (uint32_t)4U * i + (uint32_t)2U);
                  {
                    uint64_t t12 = t01[(uint32_t)4U * i + (uint32_t)3U];
                    uint64_t t2 = t231[(uint32_t)4U * i + (uint32_t)3U];
                    c11 =
                      Lib_IntTypes_Intrinsics_sub_borrow_u64(c11,
                        t12,
                        t2,
                        t45 + (uint32_t)4U * i + (uint32_t)3U);
                  }
                }
              }
            }
          }
          {
            uint32_t i;
            for (i = k3; i < aLen; i++)
            {
              uint64_t t1 = t01[i];
              uint64_t t2 = t231[i];
              c11 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c11, t1, t2, t45 + i);
            }
          }
          c3 = c11;
          c5 = c2 - c3;
          {
            uint32_t aLen2 = aLen / (uint32_t)2U;
            uint64_t *r0 = res + aLen2;
            uint64_t c12 = (uint64_t)0U;
            uint32_t k4 = aLen / (uint32_t)4U * (uint32_t)4U;
            uint64_t r10;
            uint64_t c6;
            uint64_t c7;
            {
              uint32_t i;
              for (i = (uint32_t)0U; i < k4 / (uint32_t)4U; i++)
              {
                uint64_t t1 = r0[(uint32_t)4U * i];
                uint64_t t20 = t45[(uint32_t)4U * i];
                c12 = Lib_IntTypes_Intrinsics_add_carry_u64(c12, t1, t20, r0 + (uint32_t)4U * i);
                {
                  uint64_t t10 = r0[(uint32_t)4U * i + (uint32_t)1U];
                  uint64_t t21 = t45[(uint32_t)4U * i + (uint32_t)1U];
                  c12 =
                    Lib_IntTypes_Intrinsics_add_carry_u64(c12,
                      t10,
                      t21,
                      r0 + (uint32_t)4U * i + (uint32_t)1U);
                  {
                    uint64_t t11 = r0[(uint32_t)4U * i + (uint32_t)2U];
                    uint64_t t22 = t45[(uint32_t)4U * i + (uint32_t)2U];
                    c12 =
                      Lib_IntTypes_Intrinsics_add_carry_u64(c12,
                        t11,
                        t22,
                        r0 + (uint32_t)4U * i + (uint32_t)2U);
                    {
                      uint64_t t12 = r0[(uint32_t)4U * i + (uint32_t)3U];
                      uint64_t t2 = t45[(uint32_t)4U * i + (uint32_t)3U];
                      c12 =
                        Lib_IntTypes_Intrinsics_add_carry_u64(c12,
                          t12,
                          t2,
                          r0 + (uint32_t)4U * i + (uint32_t)3U);
                    }
                  }
                }
              }
            }
            {
              uint32_t i;
              for (i = k4; i < aLen; i++)
              {
                uint64_t t1 = r0[i];
                uint64_t t2 = t45[i];
                c12 = Lib_IntTypes_Intrinsics_add_carry_u64(c12, t1, t2, r0 + i);
              }
            }
            r10 = c12;
            c6 = r10;
            c7 = c5 + c6;
            {
              uint64_t c71 = c7;
              uint64_t *r = res + aLen + aLen2;
              uint64_t *a01 = r;
              uint64_t *res0 = r;
              uint64_t c13 = (uint64_t)0U;
              uint32_t k5 = (uint32_t)0U;
              uint64_t c01;
              uint64_t r1;
              uint64_t c8;
              uint64_t c14;
              uint64_t c15;
              {
                uint32_t i;
                for (i = (uint32_t)0U; i < k5 / (uint32_t)4U; i++)
                {
                  uint64_t t1 = a01[(uint32_t)4U * i];
                  uint64_t t20 = (&c71)[(uint32_t)4U * i];
                  c13 = Lib_IntTypes_Intrinsics_add_carry_u64(c13, t1, t20, res0 + (uint32_t)4U * i);
                  {
                    uint64_t t10 = a01[(uint32_t)4U * i + (uint32_t)1U];
                    uint64_t t21 = (&c71)[(uint32_t)4U * i + (uint32_t)1U];
                    c13 =
                      Lib_IntTypes_Intrinsics_add_carry_u64(c13,
                        t10,
                        t21,
                        res0 + (uint32_t)4U * i + (uint32_t)1U);
                    {
                      uint64_t t11 = a01[(uint32_t)4U * i + (uint32_t)2U];
                      uint64_t t22 = (&c71)[(uint32_t)4U * i + (uint32_t)2U];
                      c13 =
                        Lib_IntTypes_Intrinsics_add_carry_u64(c13,
                          t11,
                          t22,
                          res0 + (uint32_t)4U * i + (uint32_t)2U);
                      {
                        uint64_t t12 = a01[(uint32_t)4U * i + (uint32_t)3U];
                        uint64_t t2 = (&c71)[(uint32_t)4U * i + (uint32_t)3U];
                        c13 =
                          Lib_IntTypes_Intrinsics_add_carry_u64(c13,
                            t12,
                            t2,
                            res0 + (uint32_t)4U * i + (uint32_t)3U);
                      }
                    }
                  }
                }
              }
              {
                uint32_t i;
                for (i = k5; i < (uint32_t)1U; i++)
                {
                  uint64_t t1 = a01[i];
                  uint64_t t2 = (&c71)[i];
                  c13 = Lib_IntTypes_Intrinsics_add_carry_u64(c13, t1, t2, res0 + i);
                }
              }
              c01 = c13;
              if ((uint32_t)1U < aLen + aLen - (aLen + aLen2))
              {
                uint32_t rLen = aLen + aLen - (aLen + aLen2) - (uint32_t)1U;
                uint64_t *a11 = r + (uint32_t)1U;
                uint64_t *res1 = r + (uint32_t)1U;
                uint64_t c = c01;
                uint32_t k = rLen / (uint32_t)4U * (uint32_t)4U;
                {
                  uint32_t i;
                  for (i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
                  {
                    uint64_t t1 = a11[(uint32_t)4U * i];
                    c =
                      Lib_IntTypes_Intrinsics_add_carry_u64(c,
                        t1,
                        (uint64_t)0U,
                        res1 + (uint32_t)4U * i);
                    {
                      uint64_t t10 = a11[(uint32_t)4U * i + (uint32_t)1U];
                      c =
                        Lib_IntTypes_Intrinsics_add_carry_u64(c,
                          t10,
                          (uint64_t)0U,
                          res1 + (uint32_t)4U * i + (uint32_t)1U);
                      {
                        uint64_t t11 = a11[(uint32_t)4U * i + (uint32_t)2U];
                        c =
                          Lib_IntTypes_Intrinsics_add_carry_u64(c,
                            t11,
                            (uint64_t)0U,
                            res1 + (uint32_t)4U * i + (uint32_t)2U);
                        {
                          uint64_t t12 = a11[(uint32_t)4U * i + (uint32_t)3U];
                          c =
                            Lib_IntTypes_Intrinsics_add_carry_u64(c,
                              t12,
                              (uint64_t)0U,
                              res1 + (uint32_t)4U * i + (uint32_t)3U);
                        }
                      }
                    }
                  }
                }
                {
                  uint32_t i;
                  for (i = k; i < rLen; i++)
                  {
                    uint64_t t1 = a11[i];
                    c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t1, (uint64_t)0U, res1 + i);
                  }
                }
                {
                  uint64_t c16 = c;
                  r1 = c16;
                }
              }
              else
              {
                r1 = c01;
              }
              c8 = r1;
              c14 = c8;
              c15 = c14;
            }
          }
        }
      }
    }
  }
}
