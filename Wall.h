/***************************************
 * Wall header (for ROS message comm)
 * UMKC Robot Team 2013
 * Eric Gonzalez
 * Started: February 16, 2013
 * Updated: March 27, 2013
 ***************************************/

#ifndef ros_capstone_Wall_h
#define ros_capstone_Wall_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../ros_lib/ros/msg.h"
#include "std_msgs/Header.h"

namespace capstone
{

  class Wall : public ros::Msg
  {
    public:
      std_msgs::Header header;
      unsigned char device_id;
      unsigned int size;
      char * data;

    virtual int serialize(unsigned char *outbuffer)
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        unsigned char real;
        unsigned char base;
      } u_device_id;
      u_device_id.real = this->device_id;
      *(outbuffer + offset + 0) = (u_device_id.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->device_id);
      union {
        unsigned int real;
        unsigned int base;
      } u_size;
      u_size.real = this->size;
      *(outbuffer + offset + 0) = (u_size.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_size.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->size);
      long * length_data = (long *)(outbuffer + offset);
      *length_data = strlen( (const char*) this->data);
      offset += 4;
      memcpy(outbuffer + offset, this->data, *length_data);
      offset += *length_data;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        unsigned char real;
        unsigned char base;
      } u_device_id;
      u_device_id.base = 0;
      u_device_id.base |= ((typeof(u_device_id.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      this->device_id = u_device_id.real;
      offset += sizeof(this->device_id);
      union {
        unsigned int real;
        unsigned int base;
      } u_size;
      u_size.base = 0;
      u_size.base |= ((typeof(u_size.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_size.base |= ((typeof(u_size.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      this->size = u_size.real;
      offset += sizeof(this->size);
      uint32_t length_data = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_data; ++k){
          inbuffer[k-1]=inbuffer[k];
           }
      inbuffer[offset+length_data-1]=0;
      this->data = (char *)(inbuffer + offset-1);
      offset += length_data;
     return offset;
    }

    const char * getType(){ return "capstone/Wall"; };

  };

};
#endif
