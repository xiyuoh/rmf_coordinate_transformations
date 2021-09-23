/*
 * Copyright (C) 2021 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include <rmf_utils/catch.hpp>
#include <rmf_proj/Transform.hpp>

namespace rmf_proj {

SCENARIO("Test Transform")
{
  GIVEN("Converting between EPSG:3857 and EPSG:3414")
  {
    // Reference:
    // https://epsg.io/transform#s_srs=3857&t_srs=3414&x=11542755.6413440&y=152186.1233160
    // Note that their coordinate system axes are switched
    Transform t("EPSG:3857", "EPSG:3414");

    double x = 11542755.641344;
    double y = 152186.123316;

    double svy21_x = 0.0;
    double svy21_y = 0.0;
    t.transform_1_to_2(x, y, svy21_x, svy21_y);

    REQUIRE(svy21_x == Approx(38779.86));
    REQUIRE(svy21_y == Approx(12087.97));

    t.transform_2_to_1(svy21_x, svy21_y, x, y);

    REQUIRE(x == Approx(11542755.641344));
    REQUIRE(y == Approx(152186.123316));
  }

  GIVEN("Using prebuilt WGS84PseudoMercator_SVY21_Transform class")
  {
    // Reference:
    // https://epsg.io/transform#s_srs=3857&t_srs=3414&x=11555367.7510120&y=151727.5011460
    WGS84PseudoMercator_SVY21_Transform t;

    double wgs84_x = 11555367.751012;
    double wgs84_y = 151727.501146;

    double svy21_x = 0.0;
    double svy21_y = 0.0;
    t.transform_1_to_2(wgs84_x, wgs84_y, svy21_x, svy21_y);

    REQUIRE(svy21_x == Approx(38323.98));
    REQUIRE(svy21_y == Approx(24696.53));

    t.transform_2_to_1(svy21_x, svy21_y, wgs84_x, wgs84_y);

    REQUIRE(wgs84_x == Approx(11555367.75));
    REQUIRE(wgs84_y == Approx(151727.50));
  }

  GIVEN("Using prebuilt WGS84GPS_SVY21_Transform class")
  {
    // Reference:
    // https://epsg.io/transform#s_srs=4326&t_srs=3414&x=103.8293838&y=1.3532520
    WGS84GPS_SVY21_Transform t;

    double wgs84_longtitude = 103.8293838;
    double wgs84_latitude = 1.353252;

    double svy21_x = 0.0;
    double svy21_y = 0.0;
    t.transform_1_to_2(wgs84_latitude, wgs84_longtitude, svy21_x, svy21_y);

    REQUIRE(svy21_x == Approx(37261.25));
    REQUIRE(svy21_y == Approx(27562.10));

    t.transform_2_to_1(svy21_x, svy21_y, wgs84_latitude, wgs84_longtitude);
    REQUIRE(wgs84_longtitude == Approx(103.8293838));
    REQUIRE(wgs84_latitude == Approx(1.353252));
  }
}

} // namespace rmf_proj