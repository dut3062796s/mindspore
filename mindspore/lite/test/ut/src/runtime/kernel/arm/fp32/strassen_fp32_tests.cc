/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <iostream>
#include <memory>
#include "utils/log_adapter.h"
#include "common/common_test.h"
#include "src/common/file_utils.h"
#include "mindspore/lite/src/runtime/kernel/arm/nnacl/pack.h"
#include "mindspore/lite/src/runtime/kernel/arm/nnacl/fp32/strassen_matmul.h"
#include "mindspore/lite/src/runtime/kernel/arm/nnacl/conv_parameter.h"

namespace mindspore {
class TestStrassenFp32 : public mindspore::Common {
 public:
  TestStrassenFp32() {}
};

TEST_F(TestStrassenFp32, MatrixAdd1) {
  float a[] = {0.06796285, 0.6176181,  0.33195993, 0.2752791,  0.36864007, 0.04605605, 0.33899087, 0.9820137,
               0.49804246, 0.8242412,  0.8458231,  0.6530539,  0.6336898,  0.8367749,  0.57166654, 0.25895607,
               0.90079665, 0.10585558, 0.8215811,  0.48977906, 0.7895138,  0.41816455, 0.18999523, 0.28736928,
               0.5882977,  0.44262612, 0.65245426, 0.7834421,  0.60903394, 0.82289135, 0.03855767, 0.30543327,
               0.37747085, 0,          0,          0,          0.590335,   0,          0,          0,
               0.7578682,  0,          0,          0,          0.81001425, 0,          0,          0,
               0.9487712,  0,          0,          0,          0.11742989, 0,          0,          0,
               0.60004807, 0,          0,          0,          0.05973052, 0,          0,          0};
  float b[] = {0.112120815, 0.6869974,  0.08290442, 0.43003577,  0.044390075, 0.23077105, 0.23964432, 0.4426781,
               0.6612115,   0.14988606, 0.84881437, 0.032587975, 0.35028255,  0.41838303, 0.12859282, 0.060378596,
               0.8272769,   0.6949804,  0.9120368,  0.12399232,  0.9292184,   0.7566025,  0.10235854, 0.015936268,
               0.20426726,  0.9926392,  0.54714125, 0.7022856,   0.58746314,  0.95714045, 0.26433542, 0.9030878,
               0.8596953,   0,          0,          0,           0.8341476,   0,          0,          0,
               0.72301114,  0,          0,          0,           0.40733734,  0,          0,          0,
               0.2873559,   0,          0,          0,           0.612321,    0,          0,          0,
               0.5008707,   0,          0,          0,           0.2586266,   0,          0,          0};
  float add[] = {0.18008366, 1.3046155,  0.41486436, 0.7053149, 0.41303015, 0.2768271, 0.5786352,  1.4246918,
                 1.159254,   0.9741273,  1.6946375,  0.6856419, 0.9839724,  1.255158,  0.7002593,  0.3193347,
                 1.7280736,  0.80083597, 1.7336179,  0.6137714, 1.7187322,  1.174767,  0.29235378, 0.30330554,
                 0.792565,   1.4352653,  1.1995955,  1.4857277, 1.1964971,  1.7800318, 0.3028931,  1.2085211,
                 1.2371662,  0,          0,          0,         1.4244826,  0,         0,          0,
                 1.4808793,  0,          0,          0,         1.2173516,  0,         0,          0,
                 1.2361271,  0,          0,          0,         0.72975093, 0,         0,          0,
                 1.1009188,  0,          0,          0,         0.31835714, 0,         0,          0};
  float out[64] = {0};
  MatrixAdd(a, b, out, 32, 32, 32, 8, 2);
  EXPECT_EQ(0, lite::CompareOutputData(out, add, 64));
}

TEST_F(TestStrassenFp32, MatrixAdd2) {
  float a[] = {0.06796285, 0.6176181,  0.33195993, 0.2752791,  0.36864007, 0.04605605, 0.33899087, 0.9820137,
               0.49804246, 0.8242412,  0.8458231,  0.6530539,  0.6336898,  0.8367749,  0.57166654, 0.25895607,
               0.90079665, 0.10585558, 0.8215811,  0.48977906, 0.7895138,  0.41816455, 0.18999523, 0.28736928,
               0.5882977,  0.44262612, 0.65245426, 0.7834421,  0.60903394, 0.82289135, 0.03855767, 0.30543327,
               0,          0,          0,          0,          0,          0,          0,          0,
               0,          0,          0,          0,          0.37747085, 0,          0,          0,
               0.590335,   0,          0,          0,          0.7578682,  0,          0,          0,
               0.81001425, 0,          0,          0,          0.9487712,  0,          0,          0,
               0.11742989, 0,          0,          0,          0.60004807, 0,          0,          0,
               0.05973052, 0,          0,          0,          0,          0,          0,          0,
               0,          0,          0,          0,          0,          0,          0,          0};
  float b[] = {0.112120815, 0.6869974,  0.08290442, 0.43003577,  0.044390075, 0.23077105, 0.23964432, 0.4426781,
               0.6612115,   0.14988606, 0.84881437, 0.032587975, 0.35028255,  0.41838303, 0.12859282, 0.060378596,
               0.8272769,   0.6949804,  0.9120368,  0.12399232,  0.9292184,   0.7566025,  0.10235854, 0.015936268,
               0.20426726,  0.9926392,  0.54714125, 0.7022856,   0.58746314,  0.95714045, 0.26433542, 0.9030878,
               0,           0,          0,          0,           0,           0,          0,          0,
               0,           0,          0,          0,           0,           0,          0,          0,
               0,           0,          0,          0,           0,           0,          0,          0,
               0.8596953,   0,          0,          0,           0.8341476,   0,          0,          0,
               0.72301114,  0,          0,          0,           0.40733734,  0,          0,          0,
               0.2873559,   0,          0,          0,           0.612321,    0,          0,          0,
               0.5008707,   0,          0,          0,           0.2586266,   0,          0,          0,
               0,           0,          0,          0,           0,           0,          0,          0,
               0,           0,          0,          0,           0,           0,          0,          0,
               0,           0,          0,          0,           0,           0,          0,          0};
  float add[] = {0.18008366, 1.3046155,  0.41486436, 0.7053149, 0.41303015, 0.2768271, 0.5786352,  1.4246918,
                 1.159254,   0.9741273,  1.6946375,  0.6856419, 0.9839724,  1.255158,  0.7002593,  0.3193347,
                 1.7280736,  0.80083597, 1.7336179,  0.6137714, 1.7187322,  1.174767,  0.29235378, 0.30330554,
                 0.792565,   1.4352653,  1.1995955,  1.4857277, 1.1964971,  1.7800318, 0.3028931,  1.2085211,
                 0,          0,          0,          0,         1.2371662,  0,         0,          0,
                 1.4244826,  0,          0,          0,         1.4808793,  0,         0,          0,
                 1.2173516,  0,          0,          0,         1.2361271,  0,         0,          0,
                 0.72975093, 0,          0,          0,         1.1009188,  0,         0,          0,
                 0.31835714, 0,          0,          0,         0,          0,         0,          0};
  float out[72] = {0};
  MatrixAdd(a, b, out, 44, 56, 36, 8, 2);
  EXPECT_EQ(0, lite::CompareOutputData(out, add, 72));
}

TEST_F(TestStrassenFp32, MatrixSub1) {
  float a[] = {0.4160896,  0.55011475, 0.60395557,  0.964036,   0.8010256,    0.908257,   0.60170764, 0.008877548,
               0.4973592,  0.6104505,  0.2957374,   0.39589414, 0.0151615525, 0.45663023, 0.3815148,  0.6419536,
               0.9118046,  0.5312479,  0.104496025, 0.5972911,  0.9671534,    0.7195669,  0.23360363, 0.22078007,
               0.31118092, 0.7438336,  0.5592656,   0.7212792,  0.97856164,   0.26012093, 0.18205991, 0.90656054,
               0.24593723, 0,          0,           0,          0.5024593,    0,          0,          0,
               0.42271087, 0,          0,           0,          0.48668534,   0,          0,          0,
               0.4374295,  0,          0,           0,          0.22822042,   0,          0,          0,
               0.88180095, 0,          0,           0,          0.7505223,    0,          0,          0};
  float b[] = {0.14911577, 0.63214976, 0.74834836, 0.36854064, 0.5801671,  0.24166176, 0.64528674, 0.04887214,
               0.23637155, 0.34321627, 0.69035923, 0.6114065,  0.73006815, 0.575073,   0.88130534, 0.72951907,
               0.17092401, 0.652334,   0.6288812,  0.62121505, 0.12793411, 0.16503152, 0.7564361,  0.51976234,
               0.19353953, 0.5795124,  0.6671185,  0.10646773, 0.13608798, 0.37959677, 0.24294423, 0.1790138,
               0.85054415, 0,          0,          0,          0.18541782, 0,          0,          0,
               0.72714496, 0,          0,          0,          0.43221787, 0,          0,          0,
               0.7200413,  0,          0,          0,          0.15780604, 0,          0,          0,
               0.30473796, 0,          0,          0,          0.37719592, 0,          0,          0};
  float s[] = {0.26697382, -0.082035,   -0.14439279, 0.59549534,  0.22085851, 0.6665952,   -0.0435791,  -0.03999459,
               0.26098764, 0.26723424,  -0.39462185, -0.21551237, -0.7149066, -0.11844277, -0.49979055, -0.08756548,
               0.7408806,  -0.12108606, -0.5243852,  -0.02392393, 0.8392193,  0.5545354,   -0.5228325,  -0.29898226,
               0.11764139, 0.16432118,  -0.10785288, 0.6148115,   0.8424736,  -0.11947584, -0.06088431, 0.72754675,
               -0.6046069, 0.,          0.,          0.,          0.31704146, 0.,          0.,          0.,
               -0.3044341, 0.,          0.,          0.,          0.05446747, 0.,          0.,          0.,
               -0.2826118, 0.,          0.,          0.,          0.07041438, 0.,          0.,          0.,
               0.57706296, 0.,          0.,          0.,          0.3733264,  0.,          0.,          0.};
  float out[64] = {0};
  MatrixSub(a, b, out, 32, 32, 32, 8, 2);
  EXPECT_EQ(0, lite::CompareOutputData(out, s, 64));
}

TEST_F(TestStrassenFp32, MatrixSub2) {
  float a[] = {0.4160896,  0.55011475, 0.60395557,  0.964036,   0.8010256,    0.908257,   0.60170764, 0.008877548,
               0.4973592,  0.6104505,  0.2957374,   0.39589414, 0.0151615525, 0.45663023, 0.3815148,  0.6419536,
               0.9118046,  0.5312479,  0.104496025, 0.5972911,  0.9671534,    0.7195669,  0.23360363, 0.22078007,
               0.31118092, 0.7438336,  0.5592656,   0.7212792,  0.97856164,   0.26012093, 0.18205991, 0.90656054,
               0.24593723, 0,          0,           0,          0.5024593,    0,          0,          0,
               0.42271087, 0,          0,           0,          0.48668534,   0,          0,          0,
               0.4374295,  0,          0,           0,          0.22822042,   0,          0,          0,
               0.88180095, 0,          0,           0,          0.7505223,    0,          0,          0};
  float b[] = {0.14911577, 0.63214976, 0.74834836, 0.36854064, 0.5801671,  0.24166176, 0.64528674, 0.04887214,
               0.23637155, 0.34321627, 0.69035923, 0.6114065,  0.73006815, 0.575073,   0.88130534, 0.72951907,
               0.17092401, 0.652334,   0.6288812,  0.62121505, 0.12793411, 0.16503152, 0.7564361,  0.51976234,
               0.19353953, 0.5795124,  0.6671185,  0.10646773, 0.13608798, 0.37959677, 0.24294423, 0.1790138,
               0,          0,          0,          0,          0,          0,          0,          0,
               0,          0,          0,          0,          0.85054415, 0,          0,          0,
               0.18541782, 0,          0,          0,          0.72714496, 0,          0,          0,
               0.43221787, 0,          0,          0,          0.7200413,  0,          0,          0,
               0.15780604, 0,          0,          0,          0.30473796, 0,          0,          0,
               0.37719592, 0,          0,          0,          0,          0,          0,          0,
               0,          0,          0,          0,          0,          0,          0,          0};
  float s[] = {0.26697382, -0.082035,   -0.14439279, 0.59549534,  0.22085851, 0.6665952,   -0.0435791,  -0.03999459,
               0.26098764, 0.26723424,  -0.39462185, -0.21551237, -0.7149066, -0.11844277, -0.49979055, -0.08756548,
               0.7408806,  -0.12108606, -0.5243852,  -0.02392393, 0.8392193,  0.5545354,   -0.5228325,  -0.29898226,
               0.11764139, 0.16432118,  -0.10785288, 0.6148115,   0.8424736,  -0.11947584, -0.06088431, 0.72754675,
               0,          0,           0,           0,           -0.6046069, 0.,          0.,          0.,
               0.31704146, 0.,          0.,          0.,          -0.3044341, 0.,          0.,          0.,
               0.05446747, 0.,          0.,          0.,          -0.2826118, 0.,          0.,          0.,
               0.07041438, 0.,          0.,          0.,          0.57706296, 0.,          0.,          0.,
               0.3733264,  0.,          0.,          0,           0,          0,           0,           0.};
  float out[72] = {0};
  MatrixSub(a, b, out, 32, 44, 36, 8, 2);
  EXPECT_EQ(0, lite::CompareOutputData(out, s, 72));
}

TEST_F(TestStrassenFp32, MatrixPack1) {
  float in[] = {4.1795, 13.142, -3.593, 16.505, 19.969, -6.235, -2.380, -9.027, 23.622, 8.3608, 47.325, -14.36,
                -0.784, 37.925, -0.081, 6.1298, 37.998, 13.719, 11.029, 1.7127, 9.0560, 14.988, 3.1866, 0.0562,
                14.530, -14.10, -8.115, -8.071, 19.250, 17.923, 13.584, 3.3293, -1.514, -0.293, 18.686, 0.0873,
                19.899, 8.5562, 0.0,    0.0,    9.5542, 18.974, 0.0,    0.0,    15.370, 4.3049, 0.0,    0.0,
                0.6721, -1.517, 0.0,    0.0,    -1.770, 41.903, 0.0,    0.0,    8.1381, 9.1391, 0.0,    0.0,
                -8.158, 7.7566, 0.0,    0.0,    9.7341, 18.834, 0.0,    0.0,    4.2010, -2.253, 0.0,    0.0};
  float correct[] = {4.1795, 13.142, -3.593, 16.505, 19.969, -6.235, -2.380, -9.027, 23.622, 8.3608, 47.325, -14.36,
                     -0.784, 37.925, -0.081, 6.1298, 19.899, 8.5562, 0.0,    0.0,    9.5542, 18.974, 0.0,    0.0,
                     15.370, 4.3049, 0.0,    0.0,    0.6721, -1.517, 0.0,    0.0,    37.998, 13.719, 11.029, 1.7127,
                     9.0560, 14.988, 3.1866, 0.0562, 14.530, -14.10, -8.115, -8.071, -1.770, 41.903, 0.0,    0.0,
                     8.1381, 9.1391, 0.0,    0.0,    -8.158, 7.7566, 0.0,    0.0};
  float out[56] = {0};

  MatrixPack(in, out, 7, 2, 36);
  EXPECT_EQ(0, lite::CompareOutputData(out, correct, 56));
}

TEST_F(TestStrassenFp32, MatrixPack2) {
  float in[] = {4.1795, 13.142, -3.593, 16.505, 19.969, -6.235, -2.380, -9.027, 23.622, 8.3608, 47.325, -14.36,
                -0.784, 37.925, -0.081, 6.1298, 37.998, 13.719, 11.029, 1.7127, 9.0560, 14.988, 3.1866, 0.0562,
                14.530, -14.10, -8.115, -8.071, 19.250, 17.923, 13.584, 3.3293, -1.514, -0.293, 18.686, 0.0873,
                19.899, 8.5562, 0.0,    0.0,    9.5542, 18.974, 0.0,    0.0,    15.370, 4.3049, 0.0,    0.0,
                0.6721, -1.517, 0.0,    0.0,    -1.770, 41.903, 0.0,    0.0,    8.1381, 9.1391, 0.0,    0.0,
                -8.158, 7.7566, 0.0,    0.0,    9.7341, 18.834, 0.0,    0.0,    4.2010, -2.253, 0.0,    0.0};
  float correct[] = {4.1795, 13.142, -3.593, 16.505, 19.969, -6.235, -2.380, -9.027, 23.622, 8.3608, 47.325, -14.36,
                     -0.784, 37.925, -0.081, 6.1298, 19.899, 8.5562, 0.0,    0.0,    9.5542, 18.974, 0.0,    0.0,
                     15.370, 4.3049, 0.0,    0.0,    0.6721, -1.517, 0.0,    0.0,    37.998, 13.719, 11.029, 1.7127,
                     9.0560, 14.988, 3.1866, 0.0562, 14.530, -14.10, -8.115, -8.071, 19.250, 17.923, 13.584, 3.3293,
                     -1.770, 41.903, 0.0,    0.0,    8.1381, 9.1391, 0.0,    0.0,    -8.158, 7.7566, 0.0,    0.0,
                     9.7341, 18.834, 0.0,    0.0,    -1.514, -0.293, 18.686, 0.0873, 4.2010, -2.253, 0.0,    0.0};
  float out[72] = {0};
  MatrixPack(in, out, 9, 2, 36);
  EXPECT_EQ(0, lite::CompareOutputData(out, correct, 72));
}

TEST_F(TestStrassenFp32, CommonMatmul1) {
  float a_ptr[] = {7.756654,   19.250782, 17.923292,  0, 13.584222, 3.3293908, 9.734102,  0,
                   18.83455,   -1.51425,  -0.29382,   0, 18.686155, 0.0873076, 4.2010098, 0,
                   -2.2539594, 4.1795673, 13.14235,   0, -3.59393,  16.50578,  19.899279, 0,
                   8.556229,   19.969376, -6.2355065, 0, -2.380469, -9.027744, 9.5542,    0};
  float b_ptr[] = {0.2674241, 0.089372,  -0.081915, 2.0580146, -0.295045, 1.377944, 0.703658, 1.055378,
                   1.204049,  -0.256505, -0.309640, 0.560465,  0,         0,        0,        0,
                   0.646906,  0,         0,         0,         -0.168206, 0,        0,        0,
                   -0.95630,  0,         0,         0,         0,         0,        0,        0};
  float correct[] = {17.97499,  22.622334,  7.360805,  46.325558, 14.37076,  3.304931,  -1.784072, 36.925926,
                     5.129812,  -0.3278886, -2.517368, 36.99899,  10.029593, 0.7127603, -2.77004,  40.90305,
                     13.988123, 2.186689,   -0.943787, 7.138184,  18.128653, 17.31859,  5.7472067, 21.176342,
                     -11.11159, 29.880829,  15.281498, 35.1893,   13.530734, -15.10318, -9.11581,  -9.071925,
                     -15.36046, 0,          0,         0,         -1.081104, 0,         0,         0,
                     12.719885, 0,          0,         0,         8.056052,  0,         0,         0,
                     -14.72927, 0,          0,         0,         -24.1311,  0,         0,         0,
                     8.139168,  0,          0,         0,         -9.158176, 0,         0,         0};
  StrassenMatMulParameter *matmul_param = new StrassenMatMulParameter();
  matmul_param->row_ = 8;
  matmul_param->deep_ = 1;
  matmul_param->col_ = 2;
  matmul_param->a_stride_ = 32;
  matmul_param->b_stride_ = 16;
  matmul_param->c_stride_ = 32;

  float c_ptr[64] = {0};
  float tmp_ptr[32];
  CommonMatMul(a_ptr, b_ptr, c_ptr, matmul_param, tmp_ptr);

  EXPECT_EQ(0, lite::CompareOutputData(c_ptr, correct, 64));
  delete matmul_param;
}

TEST_F(TestStrassenFp32, CommonMatmul2) {
  StrassenMatMulParameter *matmul_param = new StrassenMatMulParameter();
  float a[] = {4.864725,   6.830073,  0.76780415, 8.922394,  5.096872,  2.4946148,  4.2148714, 1.7762588, 0.89195687,
               9.703938,   2.0654619, 9.048538,   2.358036,  5.643526,  2.5152204,  3.512572,  3.7913973, 3.7136157,
               8.820186,   1.5324963, 3.135459,   7.5792265, 7.1820426, 0.267987,   8.737802,  4.064117,  2.7232447,
               0.27355433, 0,         0,          0,         0,         0,          0,         0,         0,
               6.320409,   9.479354,  0,          0,         1.6220464, 0.57753897, 0,         0,         9.786372,
               6.0404425,  0,         0,          2.1067812, 4.8034563, 0,          0,         2.1140356, 8.204062,
               0,          0,         3.29985,    1.2034118, 0,         0,          7.6059656, 4.162436,  0,
               0,          0,         0,          0,         0,         0,          0,         0,         0,
               0,          0,         0,          0,         0,         0,          0,         0,         0,
               0,          0,         0,          0,         0,         0,          0,         0,         0,
               0,          0,         0,          0,         0,         0,          0,         0,         0,
               0,          0,         0,          0,         0,         0,          0,         0,         0,
               0,          0,         0,          0,         0,         0,          0,         0,         0,
               0,          0,         0,          0,         0,         0,          0,         0,         0,
               0,          0,         0,          0,         0,         0,          0,         0,         0,
               0,          0,         0,          0,         0,         0,          0,         0,         0};

  float b[] = {
    4.4558744,  0.6383263, 0.05037839, 9.730914, 8.1542015, 4.3625517, 8.654026,   3.805875,  9.845131,  4.08051,
    9.667656,   7.73955,   9.283867,   8.465257, 2.292051,  9.853942,  0.13320169, 3.8789113, 9.460265,  4.2616735,
    0.23831692, 4.420147,  0.5355651,  7.829217, 0,         0,         0,          0,         0,         0,
    0,          0,         0,          0,        0,         0,         0,          0,         0,         0,
    0,          0,         0,          0,        0,         0,         0,          0,         0,         0,
    0,          0,         0,          0,        0,         0,         0,          0,         0,         0,
    0,          0,         0,          0,        1.9866786, 0,         0,          0,         6.0188327, 0,
    0,          0,         6.6249146,  0,        0,         0,         3.5639563,  0,         0,         0,
    0.14810833, 0,         0,          0,        7.4168983, 0,         0,          0,         0,         0,
    0,          0,         0,          0,        0,         0,         0,          0,         0,         0,
    0,          0,         0,          0,        0,         0,         0,          0,         0,         0,
    0,          0,         0,          0,        0,         0,         0,          0,         0,         0,
    0,          0,         0,          0,        0,         0,         0,          0};
  float c[] = {170.86482, 177.98166, 152.0957,  268.3473,  101.39282, 55.216248, 82.31873,  120.65008, 190.18558,
               192.58974, 220.54767, 239.75931, 115.32386, 95.52758,  103.82857, 145.08948, 150.4757,  112.04814,
               145.50496, 207.63342, 149.6962,  84.76027,  167.65851, 141.06763, 103.42963, 84.63687,  136.74927,
               189.26935, 0,         0,         0,         0,         0,         0,         0,         0,
               0,         0,         0,         0,         158.90288, 0,         0,         0,         63.917973,
               0,         0,         0,         152.3613,  0,         0,         0,         103.77265, 0,
               0,         0,         154.94044, 0,         0,         0,         109.79707, 0,         0,
               0,         92.83551,  0,         0,         0,         0,         0,         0,         0,
               0,         0,         0,         0,         0,         0,         0,         0};

  matmul_param->row_ = 7;
  matmul_param->deep_ = 2;
  matmul_param->col_ = 2;
  matmul_param->a_stride_ = 36;
  matmul_param->b_stride_ = 64;
  matmul_param->c_stride_ = 40;
  float out[80] = {0};
  float tmp_ptr[1000];
  CommonMatMul(a, b, out, matmul_param, tmp_ptr);
  EXPECT_EQ(0, lite::CompareOutputData(out, c, 80));
  delete (matmul_param);
}

TEST_F(TestStrassenFp32, RecMatmul1) {
  StrassenMatMulParameter *matmul_param = new StrassenMatMulParameter();
  matmul_param->row_ = 4;
  matmul_param->deep_ = 2;
  matmul_param->col_ = 2;
  matmul_param->a_stride_ = 16;
  matmul_param->b_stride_ = 32;
  matmul_param->c_stride_ = 16;

  float a[] = {9.02165,  8.657163,   0.56371903, 0.7272156, 1.6258951,  9.919627,   7.47593,   3.5311592,
               8.958062, 0.55338514, 9.611276,   7.429841,  8.23804,    3.7503464,  1.2829816, 6.4470887,
               4.303486, 6.282502,   0,          0,         9.4194765,  7.8199654,  0,         0,
               6.738705, 7.5398073,  0,          0,         0.47684374, 0.87746763, 0,         0};
  float b[] = {1.8100919,  6.016964,  5.733568, 5.768448,   2.2823029, 2.173359,  0.56861514, 7.134393,
               0.26377398, 3.9010656, 4.868408, 0.33401546, 1.7973539, 8.21896,   5.62239,    8.54786,
               0.97356945, 1.0714527, 6.447588, 6.161091,   3.332229,  2.8775468, 6.558747,   2.6986659,
               0,          0,         0,        0,          0,         0,         0,          0,
               1.9830805,  0,         0,        0,          8.44718,   0,         0,          0,
               9.360418,   0,         0,        0,          6.220693,  0,         0,          0,
               1.8369701,  0,         0,        0,          4.3965054, 0,         0,          0,
               0,          0,         0,        0,          0,         0,         0,          0};
  float c[] = {62.668518, 103.9633,  132.43439, 163.67749, 69.12974,  122.12326, 183.23413,  191.96806,
               65.052124, 182.57918, 233.14148, 184.20694, 38.785316, 118.74806, 100.689575, 135.12036,
               136.34613, 0,         0,         0,         230.64507, 0,         0,          0,
               204.15103, 0,         0,         0,         104.86488, 0,         0,          0};
  float out[32] = {0};

  float tmp_ptr[1000];
  RecursionMatmul(a, b, out, matmul_param, 1, 0, tmp_ptr);
  EXPECT_EQ(0, lite::CompareOutputData(out, c, 32));
  delete (matmul_param);
}

TEST_F(TestStrassenFp32, RecMatmul2) {
  StrassenMatMulParameter *matmul_param = new StrassenMatMulParameter();
  matmul_param->row_ = 4;
  matmul_param->deep_ = 2;
  matmul_param->col_ = 2;
  matmul_param->a_stride_ = 32;
  matmul_param->b_stride_ = 64;
  matmul_param->c_stride_ = 32;

  float a[] = {9.02165,  8.657163,   0.56371903, 0.7272156, 1.6258951,  9.919627,   7.47593,   3.5311592,
               8.958062, 0.55338514, 9.611276,   7.429841,  8.23804,    3.7503464,  1.2829816, 6.4470887,
               1,        2,          3,          4,         1,          2,          3,         4,
               3,        2,          3,          4,         4,          2,          3,         4,
               4.303486, 6.282502,   0,          0,         9.4194765,  7.8199654,  0,         0,
               6.738705, 7.5398073,  0,          0,         0.47684374, 0.87746763, 0,         0,
               1,        2,          3,          4,         1,          2,          3,         4,
               3,        2,          3,          4,         4,          2,          3,         4};
  float b[] = {
    1.8100919, 6.016964,   5.733568,  5.768448,  2.2823029, 2.173359, 0.56861514, 7.134393,  0.26377398, 3.9010656,
    4.868408,  0.33401546, 1.7973539, 8.21896,   5.62239,   8.54786,  0.97356945, 1.0714527, 6.447588,   6.161091,
    3.332229,  2.8775468,  6.558747,  2.6986659, 0,         0,        0,          0,         0,          0,
    0,         0,          11,        2,         3,         4,        22,         2,         3,          4,
    33,        3,          3,         4,         44,        2,        3,          4,         11,         2,
    3,         4,          22,        2,         3,         4,        33,         3,         3,          4,
    44,        2,          3,         4,         1.9830805, 0,        0,          0,         8.44718,    0,
    0,         0,          9.360418,  0,         0,         0,        6.220693,   0,         0,          0,
    1.8369701, 0,          0,         0,         4.3965054, 0,        0,          0,         0,          0,
    0,         0,          0,         0,         0,         0,        11,         2,         3,          4,
    22,        2,          3,         4,         33,        3,        3,          4,         44,         2,
    3,         4,          11,        2,         3,         4,        22,         2,         3,          4,
    33,        3,          3,         4,         44,        2,        3,          4};
  float c[] = {62.668518, 103.9633,  132.43439, 163.67749, 69.12974,  122.12326, 183.23413,  191.96806,
               65.052124, 182.57918, 233.14148, 184.20694, 38.785316, 118.74806, 100.689575, 135.12036,
               0,         0,         0,         0,         0,         0,         0,          0,
               0,         0,         0,         0,         0,         0,         0,          0,
               136.34613, 0,         0,         0,         230.64507, 0,         0,          0,
               204.15103, 0,         0,         0,         104.86488, 0,         0,          0,
               0,         0,         0,         0,         0,         0,         0,          0,
               0,         0,         0,         0,         0,         0,         0,          0};
  float out[64] = {0};

  float tmp_ptr[1000];
  RecursionMatmul(a, b, out, matmul_param, 1, 0, tmp_ptr);
  EXPECT_EQ(0, lite::CompareOutputData(out, c, 64));
  delete (matmul_param);
}
}  // namespace mindspore
