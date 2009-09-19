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

/* Author: Brian Gerkey */

/*
 * Advertise a service
 */

#include <gtest/gtest.h>

#include "ros/node.h"
#include <test_roscpp/TestStringString.h>


static int g_argc;
static char** g_argv;

class ServiceAdvertiser : public testing::Test
{
  public:
    ros::Node* n;
    bool advertised;
    bool failure;
    bool thread;

    bool srvCallback(test_roscpp::TestStringString::Request  &req,
                     test_roscpp::TestStringString::Response &res)
    {
      puts("in callback");
      if(!advertised)
      {
        puts("but not advertised!");
        failure = true;
      }
      // Can't do this for now; unadvertise() in service callback and in
      // other thread causes race conditions
      /*
      else
      {
        unadv();
        advertised = false;
      }
      */
      return true;
    }
  protected:
    ServiceAdvertiser() {}
    void SetUp()
    {
      ros::init(g_argc, g_argv);
      failure = false;
      advertised = false;

      ASSERT_TRUE(g_argc == 2);
      if(!strcmp(g_argv[1],"nothread"))
      {
        thread = false;
        n = new ros::Node("advertiser",ros::Node::DONT_START_SERVER_THREAD);
      }
      else
      {
        thread = true;
        n = new ros::Node("advertiser" );
      }
    }
    void TearDown()
    {
      
      delete n;
    }

    bool adv()
    {
      puts("advertising");
      bool ret = n->advertiseService("service_adv",
                                      &ServiceAdvertiser::srvCallback, this);
      puts("advertised");
      return ret;
    }
    bool unadv()
    {
      puts("unadvertising");
      bool ret = n->unadvertiseService("service_adv");
      puts("unadvertised");
      return ret;
    }
};

TEST_F(ServiceAdvertiser, advUnadv)
{
  advertised = true;
  ASSERT_TRUE(adv());

  for(int i=0;i<100;i++)
  {
    if(advertised)
    {
      ASSERT_TRUE(unadv());
      advertised = false;
    }
    else
    {
      advertised = true;
      ASSERT_TRUE(adv());
    }

    // Sleep for 10ms
    if(thread)
    {
      struct timespec sleep_time = {0, 10000000};
      nanosleep(&sleep_time,NULL);
    }
    else
      n->tcprosServerUpdate();
  }

  if(failure)
    FAIL();
  else
    SUCCEED();
}

int
main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  g_argc = argc;
  g_argv = argv;
  return RUN_ALL_TESTS();
}

