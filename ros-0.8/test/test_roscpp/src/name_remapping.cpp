/*
 * Copyright (c) 2008, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* Author: Josh Faust */

/*
 * Test name remapping.  Assumes the parameter "test" is remapped to "test_remap", and the node name is remapped to "name_remapped"
 */

#include <string>
#include <sstream>
#include <fstream>

#include <gtest/gtest.h>

#include <time.h>
#include <stdlib.h>

#include "ros/node.h"

ros::Node* g_node;
const char* g_node_name = "test_node";
const char* g_expected_name = "/name_remapped";
const char* g_parameter = "test";

TEST(roscpp, parameterRemapping)
{
  std::string param;
  ASSERT_TRUE(g_node->getParam(g_parameter, param));
}

TEST(roscpp, nodeNameRemapping)
{
  std::string node_name = g_node->getName();
  ASSERT_STREQ(node_name.c_str(), g_expected_name);
}

TEST(roscpp, cleanName)
{
  ASSERT_STREQ(g_node->cleanName("////asdf///").c_str(), "/asdf");
  ASSERT_STREQ(g_node->cleanName("////asdf///jioweioj").c_str(), "/asdf/jioweioj");
  ASSERT_STREQ(g_node->cleanName("////asdf///jioweioj/").c_str(), "/asdf/jioweioj");
}

int
main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  ros::init( argc, argv );

  g_node = new ros::Node( g_node_name );

  int ret = RUN_ALL_TESTS();


  delete g_node;

  return ret;
}
