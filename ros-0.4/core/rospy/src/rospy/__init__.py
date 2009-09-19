# Software License Agreement (BSD License)
#
# Copyright (c) 2008, Willow Garage, Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#  * Neither the name of Willow Garage, Inc. nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# Copyright (c) 2008, Willow Garage, Inc.
# Revision $Id$

from roslib.rosenv import ROS_ROOT, ROS_MASTER_URI, ROS_HOSTNAME, ROS_NAMESPACE, ROS_PACKAGE_PATH, ROS_LOG_DIR

import rospy.core
import rospy.init

# import symbols into rospy namespace
# NOTE: there are much better ways to configure python module
# dictionaries, but the rospy codebase isn't quite in shape for that
# yet

from roslib.msg import Header

from rospy.client import spin, myargv, init_node, \
    get_master, get_published_topics, wait_for_service, \
    get_param, get_param_names, set_param, delete_param, has_param
from rospy.core import is_shutdown, signal_shutdown, add_shutdown_hook,\
    get_node_uri, get_ros_root, \
    logdebug, logwarn, logout, logerr, logfatal, \
    parse_rosrpc_uri, \
    Time, Duration
from rospy.exceptions import *
from rospy.init import get_node_proxy
from rospy.msg import AnyMsg, Message
from rospy.names import get_caller_id, get_namespace, resolve_name
from rospy.rostime import get_rostime, get_time, sleep 
from rospy.service import ServiceException, ServiceDefinition
# - use tcp ros implementation of services
from rospy.tcpros_service import Service, ServiceProxy 
from rospy.topics import SubscribeListener, Publisher, Subscriber

# - deprecated api
from rospy.client import ready
from rospy.topics import TopicSub, TopicPub

## \defgroup validators Validators
## \defgroup clientapi Client API

