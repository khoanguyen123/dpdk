/*-
 *   BSD LICENSE
 *
 *   Copyright(c) 2016-2017 Intel Corporation. All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <rte_crypto.h>
#include <rte_malloc.h>

#include "cperf_test_vectors.h"

uint8_t plaintext[2048] = {
	0x71, 0x75, 0x83, 0x98, 0x75, 0x42, 0x51, 0x09, 0x94, 0x02, 0x13, 0x20,
	0x15, 0x64, 0x46, 0x32, 0x08, 0x18, 0x91, 0x82, 0x86, 0x52, 0x23, 0x93,
	0x44, 0x54, 0x28, 0x68, 0x78, 0x78, 0x70, 0x06, 0x42, 0x74, 0x41, 0x27,
	0x73, 0x38, 0x53, 0x77, 0x51, 0x96, 0x53, 0x24, 0x03, 0x88, 0x74, 0x14,
	0x70, 0x23, 0x88, 0x30, 0x85, 0x18, 0x89, 0x27, 0x41, 0x71, 0x61, 0x23,
	0x04, 0x83, 0x30, 0x57, 0x26, 0x47, 0x23, 0x75, 0x25, 0x62, 0x53, 0x80,
	0x38, 0x34, 0x21, 0x33, 0x34, 0x51, 0x46, 0x29, 0x94, 0x64, 0x22, 0x67,
	0x25, 0x45, 0x70, 0x26, 0x74, 0x39, 0x46, 0x71, 0x08, 0x85, 0x27, 0x18,
	0x93, 0x39, 0x72, 0x11, 0x57, 0x26, 0x88, 0x46, 0x47, 0x49, 0x86, 0x92,
	0x03, 0x37, 0x96, 0x40, 0x84, 0x53, 0x67, 0x47, 0x60, 0x60, 0x37, 0x67,
	0x02, 0x68, 0x76, 0x62, 0x42, 0x01, 0x59, 0x11, 0x01, 0x89, 0x40, 0x87,
	0x58, 0x20, 0x51, 0x21, 0x66, 0x26, 0x26, 0x73, 0x03, 0x06, 0x14, 0x25,
	0x98, 0x42, 0x44, 0x67, 0x24, 0x78, 0x71, 0x45, 0x32, 0x61, 0x20, 0x26,
	0x08, 0x88, 0x44, 0x26, 0x40, 0x63, 0x76, 0x23, 0x78, 0x55, 0x81, 0x97,
	0x95, 0x89, 0x39, 0x07, 0x14, 0x50, 0x50, 0x73, 0x07, 0x20, 0x86, 0x83,
	0x74, 0x57, 0x72, 0x36, 0x68, 0x61, 0x14, 0x41, 0x56, 0x49, 0x64, 0x72,
	0x75, 0x81, 0x47, 0x91, 0x08, 0x76, 0x47, 0x06, 0x55, 0x77, 0x61, 0x45,
	0x50, 0x10, 0x07, 0x46, 0x46, 0x89, 0x80, 0x07, 0x24, 0x95, 0x39, 0x43,
	0x03, 0x75, 0x24, 0x35, 0x57, 0x82, 0x09, 0x64, 0x29, 0x24, 0x26, 0x66,
	0x67, 0x29, 0x05, 0x90, 0x82, 0x02, 0x45, 0x71, 0x21, 0x34, 0x25, 0x48,
	0x68, 0x26, 0x01, 0x18, 0x73, 0x18, 0x46, 0x15, 0x14, 0x33, 0x28, 0x44,
	0x24, 0x82, 0x20, 0x12, 0x99, 0x43, 0x68, 0x43, 0x25, 0x14, 0x34, 0x33,
	0x31, 0x13, 0x77, 0x44, 0x95, 0x22, 0x99, 0x02, 0x30, 0x50, 0x74, 0x43,
	0x81, 0x78, 0x32, 0x17, 0x09, 0x85, 0x04, 0x37, 0x31, 0x98, 0x76, 0x79,
	0x64, 0x10, 0x39, 0x89, 0x59, 0x90, 0x50, 0x15, 0x77, 0x39, 0x28, 0x14,
	0x30, 0x19, 0x68, 0x77, 0x89, 0x48, 0x86, 0x16, 0x11, 0x33, 0x84, 0x56,
	0x10, 0x20, 0x94, 0x72, 0x41, 0x69, 0x13, 0x00, 0x56, 0x27, 0x01, 0x57,
	0x46, 0x65, 0x65, 0x19, 0x33, 0x07, 0x62, 0x19, 0x91, 0x60, 0x29, 0x11,
	0x41, 0x25, 0x88, 0x21, 0x93, 0x85, 0x87, 0x40, 0x91, 0x25, 0x32, 0x86,
	0x76, 0x54, 0x92, 0x52, 0x72, 0x46, 0x61, 0x84, 0x20, 0x14, 0x65, 0x83,
	0x69, 0x90, 0x80, 0x11, 0x35, 0x70, 0x42, 0x64, 0x74, 0x85, 0x15, 0x23,
	0x06, 0x55, 0x67, 0x49, 0x76, 0x47, 0x11, 0x95, 0x00, 0x85, 0x05, 0x12,
	0x58, 0x53, 0x25, 0x73, 0x62, 0x81, 0x63, 0x82, 0x32, 0x75, 0x16, 0x48,
	0x04, 0x96, 0x75, 0x16, 0x43, 0x83, 0x41, 0x85, 0x95, 0x67, 0x27, 0x83,
	0x22, 0x43, 0x02, 0x27, 0x69, 0x62, 0x78, 0x50, 0x57, 0x66, 0x99, 0x89,
	0x05, 0x06, 0x35, 0x86, 0x37, 0x27, 0x48, 0x46, 0x50, 0x80, 0x96, 0x40,
	0x42, 0x36, 0x21, 0x54, 0x49, 0x18, 0x63, 0x38, 0x45, 0x76, 0x23, 0x20,
	0x28, 0x06, 0x17, 0x32, 0x58, 0x50, 0x49, 0x54, 0x29, 0x46, 0x18, 0x12,
	0x17, 0x50, 0x02, 0x80, 0x99, 0x53, 0x15, 0x02, 0x07, 0x14, 0x19, 0x60,
	0x56, 0x43, 0x76, 0x71, 0x49, 0x99, 0x54, 0x83, 0x28, 0x94, 0x30, 0x30,
	0x57, 0x05, 0x89, 0x80, 0x11, 0x03, 0x78, 0x35, 0x73, 0x52, 0x67, 0x39,
	0x67, 0x07, 0x04, 0x49, 0x23, 0x83, 0x86, 0x89, 0x57, 0x71, 0x08, 0x41,
	0x15, 0x97, 0x19, 0x72, 0x03, 0x27, 0x72, 0x52, 0x66, 0x67, 0x99, 0x15,
	0x33, 0x64, 0x69, 0x78, 0x07, 0x83, 0x53, 0x71, 0x21, 0x50, 0x05, 0x48,
	0x59, 0x85, 0x01, 0x36, 0x65, 0x02, 0x52, 0x01, 0x09, 0x49, 0x28, 0x77,
	0x25, 0x35, 0x67, 0x77, 0x81, 0x64, 0x24, 0x29, 0x42, 0x32, 0x59, 0x22,
	0x93, 0x48, 0x59, 0x03, 0x85, 0x87, 0x15, 0x55, 0x23, 0x42, 0x58, 0x17,
	0x18, 0x37, 0x70, 0x83, 0x80, 0x12, 0x44, 0x83, 0x45, 0x70, 0x55, 0x86,
	0x03, 0x23, 0x01, 0x56, 0x94, 0x12, 0x41, 0x34, 0x82, 0x90, 0x83, 0x46,
	0x17, 0x56, 0x66, 0x96, 0x75, 0x80, 0x59, 0x07, 0x15, 0x84, 0x19, 0x52,
	0x37, 0x44, 0x44, 0x83, 0x72, 0x43, 0x25, 0x42, 0x26, 0x86, 0x87, 0x86,
	0x91, 0x62, 0x14, 0x90, 0x34, 0x26, 0x14, 0x33, 0x59, 0x70, 0x73, 0x15,
	0x49, 0x40, 0x66, 0x88, 0x42, 0x66, 0x16, 0x42, 0x55, 0x92, 0x82, 0x06,
	0x20, 0x96, 0x36, 0x96, 0x13, 0x07, 0x84, 0x94, 0x37, 0x66, 0x62, 0x78,
	0x60, 0x58, 0x80, 0x50, 0x69, 0x03, 0x97, 0x16, 0x64, 0x45, 0x21, 0x39,
	0x79, 0x28, 0x52, 0x17, 0x14, 0x77, 0x31, 0x60, 0x86, 0x70, 0x09, 0x53,
	0x39, 0x32, 0x52, 0x31, 0x35, 0x79, 0x24, 0x70, 0x25, 0x48, 0x23, 0x49,
	0x10, 0x64, 0x54, 0x30, 0x82, 0x34, 0x51, 0x20, 0x46, 0x04, 0x29, 0x25,
	0x65, 0x09, 0x55, 0x30, 0x30, 0x52, 0x85, 0x32, 0x79, 0x19, 0x59, 0x07,
	0x05, 0x12, 0x11, 0x03, 0x21, 0x90, 0x36, 0x62, 0x23, 0x67, 0x36, 0x67,
	0x47, 0x39, 0x92, 0x88, 0x45, 0x43, 0x71, 0x16, 0x48, 0x27, 0x68, 0x39,
	0x98, 0x38, 0x03, 0x31, 0x85, 0x10, 0x06, 0x95, 0x54, 0x79, 0x28, 0x79,
	0x56, 0x16, 0x65, 0x69, 0x00, 0x54, 0x09, 0x91, 0x06, 0x10, 0x10, 0x86,
	0x75, 0x01, 0x02, 0x71, 0x01, 0x09, 0x32, 0x94, 0x66, 0x43, 0x68, 0x36,
	0x19, 0x52, 0x02, 0x04, 0x45, 0x49, 0x40, 0x94, 0x07, 0x87, 0x86, 0x79,
	0x84, 0x07, 0x75, 0x30, 0x73, 0x02, 0x57, 0x81, 0x65, 0x02, 0x28, 0x96,
	0x57, 0x07, 0x70, 0x34, 0x39, 0x35, 0x75, 0x19, 0x47, 0x57, 0x08, 0x75,
	0x86, 0x57, 0x11, 0x32, 0x09, 0x47, 0x83, 0x93, 0x20, 0x94, 0x90, 0x88,
	0x39, 0x63, 0x22, 0x88, 0x54, 0x54, 0x95, 0x75, 0x67, 0x26, 0x02, 0x49,
	0x26, 0x17, 0x35, 0x16, 0x27, 0x65, 0x64, 0x26, 0x93, 0x92, 0x77, 0x85,
	0x84, 0x40, 0x59, 0x29, 0x49, 0x69, 0x94, 0x71, 0x72, 0x21, 0x55, 0x03,
	0x19, 0x74, 0x09, 0x40, 0x57, 0x68, 0x41, 0x19, 0x11, 0x21, 0x63, 0x56,
	0x29, 0x77, 0x57, 0x81, 0x44, 0x40, 0x76, 0x77, 0x02, 0x71, 0x66, 0x35,
	0x89, 0x02, 0x64, 0x51, 0x61, 0x02, 0x46, 0x91, 0x38, 0x93, 0x62, 0x57,
	0x18, 0x98, 0x12, 0x87, 0x29, 0x48, 0x65, 0x39, 0x99, 0x45, 0x54, 0x69,
	0x51, 0x16, 0x25, 0x75, 0x60, 0x70, 0x33, 0x72, 0x01, 0x60, 0x26, 0x51,
	0x44, 0x14, 0x39, 0x12, 0x95, 0x48, 0x87, 0x33, 0x90, 0x16, 0x42, 0x78,
	0x48, 0x58, 0x96, 0x93, 0x75, 0x23, 0x07, 0x13, 0x86, 0x07, 0x96, 0x30,
	0x22, 0x82, 0x91, 0x36, 0x72, 0x16, 0x48, 0x77, 0x64, 0x99, 0x07, 0x34,
	0x78, 0x60, 0x61, 0x13, 0x48, 0x93, 0x46, 0x62, 0x48, 0x38, 0x37, 0x96,
	0x58, 0x64, 0x39, 0x90, 0x69, 0x46, 0x81, 0x98, 0x61, 0x89, 0x15, 0x59,
	0x78, 0x98, 0x21, 0x34, 0x00, 0x69, 0x97, 0x80, 0x28, 0x81, 0x53, 0x49,
	0x79, 0x53, 0x92, 0x20, 0x29, 0x40, 0x70, 0x06, 0x09, 0x55, 0x99, 0x41,
	0x51, 0x35, 0x55, 0x27, 0x39, 0x06, 0x29, 0x83, 0x66, 0x03, 0x68, 0x14,
	0x11, 0x69, 0x95, 0x51, 0x71, 0x55, 0x24, 0x60, 0x52, 0x58, 0x88, 0x11,
	0x88, 0x25, 0x37, 0x86, 0x01, 0x52, 0x93, 0x52, 0x02, 0x24, 0x91, 0x58,
	0x56, 0x37, 0x50, 0x88, 0x39, 0x09, 0x61, 0x19, 0x08, 0x86, 0x29, 0x51,
	0x63, 0x38, 0x81, 0x14, 0x75, 0x75, 0x39, 0x99, 0x22, 0x04, 0x32, 0x63,
	0x14, 0x68, 0x41, 0x79, 0x09, 0x57, 0x87, 0x29, 0x26, 0x94, 0x05, 0x71,
	0x82, 0x41, 0x26, 0x98, 0x68, 0x18, 0x55, 0x42, 0x78, 0x05, 0x74, 0x17,
	0x34, 0x34, 0x07, 0x62, 0x94, 0x72, 0x21, 0x08, 0x54, 0x72, 0x21, 0x08,
	0x31, 0x53, 0x82, 0x35, 0x27, 0x40, 0x85, 0x77, 0x08, 0x52, 0x58, 0x48,
	0x03, 0x86, 0x65, 0x51, 0x96, 0x43, 0x89, 0x19, 0x15, 0x08, 0x49, 0x62,
	0x57, 0x46, 0x17, 0x68, 0x56, 0x04, 0x70, 0x63, 0x75, 0x88, 0x13, 0x27,
	0x87, 0x44, 0x46, 0x27, 0x02, 0x97, 0x71, 0x07, 0x40, 0x17, 0x24, 0x61,
	0x16, 0x94, 0x86, 0x85, 0x67, 0x58, 0x87, 0x92, 0x02, 0x84, 0x75, 0x19,
	0x43, 0x60, 0x68, 0x03, 0x54, 0x75, 0x33, 0x17, 0x97, 0x75, 0x12, 0x62,
	0x43, 0x08, 0x35, 0x75, 0x32, 0x21, 0x08, 0x82, 0x78, 0x04, 0x74, 0x09,
	0x13, 0x48, 0x63, 0x68, 0x67, 0x09, 0x08, 0x50, 0x11, 0x71, 0x64, 0x72,
	0x63, 0x76, 0x21, 0x62, 0x80, 0x57, 0x19, 0x15, 0x26, 0x88, 0x02, 0x26,
	0x83, 0x17, 0x61, 0x76, 0x28, 0x10, 0x22, 0x37, 0x56, 0x71, 0x51, 0x60,
	0x12, 0x79, 0x24, 0x83, 0x78, 0x47, 0x78, 0x20, 0x52, 0x27, 0x19, 0x88,
	0x81, 0x04, 0x70, 0x20, 0x25, 0x10, 0x04, 0x01, 0x72, 0x57, 0x30, 0x93,
	0x96, 0x23, 0x02, 0x94, 0x61, 0x44, 0x17, 0x65, 0x77, 0x60, 0x27, 0x43,
	0x24, 0x59, 0x46, 0x76, 0x00, 0x11, 0x31, 0x99, 0x41, 0x48, 0x75, 0x32,
	0x05, 0x15, 0x45, 0x31, 0x57, 0x89, 0x10, 0x47, 0x53, 0x14, 0x66, 0x54,
	0x60, 0x55, 0x36, 0x93, 0x30, 0x03, 0x63, 0x80, 0x65, 0x43, 0x17, 0x36,
	0x18, 0x64, 0x21, 0x38, 0x16, 0x19, 0x19, 0x51, 0x73, 0x80, 0x38, 0x27,
	0x30, 0x89, 0x13, 0x43, 0x54, 0x11, 0x78, 0x05, 0x24, 0x38, 0x83, 0x56,
	0x50, 0x59, 0x12, 0x47, 0x69, 0x70, 0x70, 0x91, 0x28, 0x02, 0x08, 0x91,
	0x66, 0x09, 0x31, 0x65, 0x46, 0x20, 0x04, 0x85, 0x89, 0x53, 0x91, 0x42,
	0x34, 0x09, 0x36, 0x92, 0x42, 0x06, 0x87, 0x88, 0x23, 0x54, 0x87, 0x85,
	0x52, 0x98, 0x95, 0x76, 0x13, 0x50, 0x59, 0x89, 0x18, 0x14, 0x17, 0x47,
	0x10, 0x97, 0x39, 0x14, 0x33, 0x79, 0x83, 0x62, 0x55, 0x18, 0x30, 0x83,
	0x03, 0x45, 0x38, 0x37, 0x35, 0x20, 0x94, 0x84, 0x89, 0x80, 0x89, 0x10,
	0x48, 0x77, 0x33, 0x36, 0x50, 0x07, 0x93, 0x02, 0x45, 0x42, 0x91, 0x12,
	0x98, 0x09, 0x77, 0x20, 0x31, 0x95, 0x10, 0x29, 0x89, 0x02, 0x38, 0x92,
	0x90, 0x19, 0x51, 0x10, 0x19, 0x82, 0x23, 0x68, 0x06, 0x00, 0x67, 0x50,
	0x25, 0x03, 0x41, 0x69, 0x53, 0x42, 0x23, 0x99, 0x29, 0x21, 0x63, 0x22,
	0x72, 0x54, 0x72, 0x40, 0x23, 0x39, 0x74, 0x92, 0x53, 0x28, 0x67, 0x56,
	0x46, 0x84, 0x59, 0x85, 0x10, 0x92, 0x31, 0x20, 0x39, 0x95, 0x65, 0x15,
	0x76, 0x35, 0x37, 0x21, 0x98, 0x41, 0x68, 0x74, 0x94, 0x94, 0x86, 0x90,
	0x35, 0x07, 0x06, 0x38, 0x78, 0x32, 0x00, 0x60, 0x86, 0x12, 0x34, 0x65,
	0x67, 0x35, 0x76, 0x94, 0x78, 0x22, 0x99, 0x42, 0x82, 0x40, 0x05, 0x74,
	0x18, 0x59, 0x03, 0x83, 0x89, 0x05, 0x19, 0x28, 0x88, 0x35, 0x59, 0x10,
	0x12, 0x96, 0x48, 0x67, 0x59, 0x87, 0x26, 0x85, 0x74, 0x64, 0x78, 0x56,
	0x91, 0x81, 0x45, 0x90, 0x21, 0x80, 0x32, 0x19, 0x61, 0x38, 0x61, 0x70,
	0x35, 0x08, 0x93, 0x53, 0x21, 0x95, 0x08, 0x27, 0x90, 0x28, 0x94, 0x27,
	0x35, 0x78, 0x03, 0x57, 0x74, 0x84, 0x73, 0x63, 0x27, 0x98, 0x14, 0x21,
	0x22, 0x36, 0x75, 0x31, 0x81, 0x65, 0x85, 0x51, 0x02, 0x45, 0x18, 0x06,
	0x39, 0x13, 0x29, 0x29, 0x73, 0x26, 0x99, 0x51, 0x38, 0x43, 0x35, 0x58,
	0x70, 0x92, 0x32, 0x13, 0x80, 0x16, 0x26, 0x44, 0x22, 0x28, 0x05, 0x45,
	0x86, 0x90, 0x38, 0x19, 0x40, 0x06, 0x30, 0x56, 0x94, 0x09, 0x02, 0x02,
	0x96, 0x29, 0x22, 0x44, 0x87, 0x38, 0x09, 0x95, 0x58, 0x46, 0x42, 0x78,
	0x72, 0x77, 0x86, 0x31, 0x97, 0x19, 0x86, 0x51, 0x73, 0x76, 0x63, 0x98,
	0x39, 0x40, 0x20, 0x20, 0x67, 0x42, 0x55, 0x50, 0x63, 0x76, 0x81, 0x87,
	0x13, 0x81, 0x19, 0x54, 0x11, 0x77, 0x90, 0x26, 0x47, 0x25, 0x92, 0x88,
	0x18, 0x56, 0x23, 0x73, 0x91, 0x52, 0x39, 0x08, 0x59, 0x51, 0x81, 0x57,
	0x78, 0x17, 0x13, 0x90, 0x90, 0x50, 0x65, 0x59, 0x99, 0x77, 0x42, 0x28,
	0x21, 0x59, 0x97, 0x64, 0x25, 0x17, 0x92, 0x24, 0x50, 0x00, 0x28, 0x40,
	0x85, 0x33, 0x78, 0x86, 0x79, 0x40, 0x28, 0x30, 0x14, 0x12, 0x01, 0x72,
	0x41, 0x43, 0x06, 0x87, 0x67, 0x31, 0x66, 0x77, 0x07, 0x50, 0x55, 0x50,
	0x22, 0x80, 0x42, 0x06, 0x38, 0x01, 0x63, 0x66, 0x70, 0x12, 0x52, 0x91,
	0x90, 0x97, 0x21, 0x28, 0x22, 0x65, 0x02, 0x80, 0x72, 0x31, 0x17, 0x76,
	0x35, 0x16, 0x03, 0x56, 0x59, 0x93, 0x36, 0x37, 0x67, 0x54, 0x46, 0x87,
	0x29, 0x01, 0x30, 0x80, 0x47, 0x47, 0x31, 0x98, 0x34, 0x30, 0x23, 0x86,
	0x86, 0x14, 0x05, 0x75, 0x09, 0x88, 0x77, 0x92, 0x59, 0x43, 0x98, 0x72,
	0x55, 0x54, 0x25, 0x59, 0x22, 0x27, 0x21, 0x62, 0x97, 0x10, 0x61, 0x73,
	0x86, 0x95, 0x99, 0x10, 0x62, 0x35, 0x25, 0x16, 0x62, 0x60, 0x51, 0x48,
	0x69, 0x69, 0x92, 0x27, 0x19, 0x43, 0x40, 0x52, 0x70, 0x23, 0x37, 0x28,
	0x73, 0x10, 0x32, 0x55, 0x85, 0x46, 0x97, 0x59, 0x88, 0x48, 0x54, 0x06,
	0x58, 0x04, 0x82, 0x98, 0x88, 0x34, 0x05, 0x41, 0x94, 0x44, 0x35, 0x10,
	0x96, 0x48, 0x21, 0x17, 0x24, 0x40, 0x26, 0x15, 0x49, 0x28, 0x12, 0x17,
	0x10, 0x17, 0x91, 0x42, 0x84, 0x15, 0x83, 0x36, 0x29, 0x49, 0x92, 0x77,
	0x74, 0x11, 0x72, 0x97, 0x64, 0x53, 0x23, 0x29, 0x16, 0x35, 0x22, 0x10,
	0x87, 0x07, 0x44, 0x78, 0x18, 0x19, 0x79, 0x03, 0x58, 0x24, 0x15, 0x63,
	0x55, 0x75, 0x56, 0x14, 0x63, 0x65, 0x86, 0x61, 0x92, 0x94, 0x30, 0x92,
	0x69, 0x78, 0x40, 0x95, 0x19, 0x81, 0x41, 0x66, 0x97, 0x00, 0x17, 0x37,
	0x20, 0x82, 0x14, 0x26, 0x42, 0x63, 0x84, 0x20, 0x96, 0x11, 0x68, 0x37,
	0x60, 0x28, 0x69, 0x85, 0x45, 0x04, 0x62, 0x20, 0x49, 0x39, 0x74, 0x84,
	0x60, 0x23, 0x38, 0x33, 0x42, 0x49, 0x38, 0x82, 0x30, 0x63, 0x21, 0x51,
	0x69, 0x09, 0x05, 0x55, 0x78, 0x90, 0x68, 0x69, 0x22, 0x20, 0x17, 0x26,
	0x54, 0x01, 0x10, 0x04, 0x68, 0x19, 0x88, 0x40, 0x91, 0x74, 0x81, 0x29,
	0x07, 0x45, 0x33, 0x77, 0x12, 0x47, 0x08, 0x60, 0x09, 0x42, 0x84, 0x15,
	0x63, 0x92, 0x64, 0x77, 0x07, 0x44, 0x11, 0x07, 0x79, 0x81, 0x24, 0x05,
	0x21, 0x60, 0x81, 0x70, 0x66, 0x36, 0x69, 0x68, 0x45, 0x01, 0x11, 0x95,
	0x67, 0x95, 0x55, 0x07, 0x96, 0x63, 0x84, 0x04, 0x74, 0x72, 0x61, 0x91,
	0x60, 0x09, 0x90, 0x14, 0x34, 0x94, 0x06, 0x12, 0x01, 0x94, 0x40, 0x14,
	0x12, 0x53, 0x64, 0x81, 0x75, 0x99, 0x36, 0x99, 0x11, 0x69, 0x95, 0x51,
	0x71, 0x55, 0x24, 0x60, 0x52, 0x58, 0x88, 0x11, 0x88, 0x25, 0x37, 0x86,
	0x66, 0x36, 0x69, 0x68, 0x45, 0x01, 0x11, 0x95
};

/* cipher text */
uint8_t ciphertext[2048] = {
	0xE2, 0x19, 0x24, 0x56, 0x13, 0x59, 0xA6, 0x5D, 0xDF, 0xD0, 0x72, 0xAA,
	0x23, 0xC7, 0x36, 0x3A, 0xBB, 0x3E, 0x8B, 0x64, 0xD5, 0xBF, 0xDE, 0x65,
	0xA2, 0x75, 0xD9, 0x45, 0x6C, 0x3C, 0xD2, 0x6A, 0xC7, 0xD0, 0x9A, 0xD0,
	0x87, 0xB8, 0xE4, 0x94, 0x11, 0x62, 0x5A, 0xC3, 0xC3, 0x01, 0xA3, 0x86,
	0xBC, 0xBC, 0x9C, 0xC0, 0x81, 0x9F, 0xBF, 0x5C, 0x6F, 0x3F, 0x13, 0xF1,
	0xAE, 0xCF, 0x26, 0xB3, 0xBC, 0x49, 0xD6, 0x3B, 0x7A, 0x2E, 0x99, 0x9E,
	0x1B, 0x04, 0x50, 0x6C, 0x48, 0x6B, 0x4E, 0x72, 0xFC, 0xC8, 0xA7, 0x0C,
	0x2C, 0xD9, 0xED, 0xE4, 0x82, 0xC4, 0x81, 0xA6, 0xB4, 0xCC, 0xAD, 0x10,
	0xF3, 0x1C, 0x39, 0x05, 0x41, 0x2D, 0x57, 0x32, 0xE7, 0x16, 0xF8, 0x4D,
	0xF0, 0xDE, 0x40, 0x5B, 0x5F, 0x80, 0xDC, 0xA7, 0xC3, 0x2D, 0x3D, 0x9E,
	0x27, 0xD4, 0xE8, 0x10, 0x8E, 0xEB, 0xA5, 0x68, 0x6F, 0x3D, 0xC0, 0x44,
	0xE7, 0x77, 0x73, 0xB9, 0x92, 0x8E, 0xA2, 0x26, 0x5C, 0x6F, 0x33, 0x4B,
	0x0B, 0xEF, 0x37, 0x55, 0xBE, 0xEC, 0x98, 0x83, 0x1E, 0xDF, 0xB2, 0x9E,
	0x5D, 0x1D, 0x78, 0x14, 0xD7, 0x85, 0x0E, 0xF8, 0x12, 0x30, 0x8E, 0x5D,
	0x08, 0x77, 0x0B, 0x2E, 0x9B, 0xF9, 0xA6, 0x72, 0xD2, 0x41, 0xC1, 0x8E,
	0x6B, 0x5E, 0x11, 0x85, 0x22, 0x6E, 0xE4, 0xA3, 0xEA, 0x4C, 0x91, 0xE1,
	0x7D, 0xD0, 0xEB, 0x9F, 0xD9, 0xD7, 0x05, 0x77, 0xD9, 0xA1, 0xC2, 0xFD,
	0x41, 0x63, 0x51, 0xB4, 0x7A, 0x1F, 0x21, 0xF0, 0xBF, 0x11, 0x4D, 0x9B,
	0x97, 0xAB, 0xB4, 0x94, 0x36, 0x34, 0xC9, 0x2D, 0x8B, 0xE2, 0x61, 0xCF,
	0xAF, 0x69, 0xD5, 0x5C, 0xE9, 0xED, 0xE3, 0xA0, 0x69, 0xD3, 0xE5, 0xAE,
	0x67, 0x6C, 0xC7, 0x11, 0xB1, 0x21, 0x96, 0xD6, 0xDB, 0xA8, 0x1D, 0xC9,
	0x83, 0x0B, 0xE2, 0xC6, 0x6E, 0x94, 0xE9, 0x50, 0x12, 0x9B, 0x01, 0x72,
	0xAA, 0xFD, 0x8B, 0x7C, 0xEC, 0x0D, 0x01, 0xA4, 0x5D, 0x00, 0xE9, 0x79,
	0x58, 0xF5, 0x67, 0xF9, 0x61, 0xC3, 0x11, 0xB4, 0x7E, 0x76, 0x0A, 0x4C,
	0x60, 0xD6, 0xBD, 0xC8, 0x31, 0xD3, 0x0C, 0xD0, 0x5B, 0xDF, 0x7B, 0x05,
	0x9A, 0xBB, 0xC6, 0x2E, 0x9F, 0xF8, 0x18, 0x80, 0x6D, 0x1B, 0x21, 0xE5,
	0xAC, 0x75, 0xBC, 0x0D, 0x72, 0x51, 0x61, 0xD7, 0xEA, 0xA2, 0xAC, 0x0E,
	0xC1, 0xE7, 0x49, 0x37, 0xE7, 0x7C, 0xDE, 0xBD, 0x56, 0x00, 0x44, 0x6D,
	0xAB, 0x81, 0x2B, 0x26, 0x4A, 0xAA, 0x60, 0xE6, 0x43, 0x8D, 0x88, 0x1C,
	0x48, 0x55, 0x53, 0x25, 0xE8, 0x3C, 0x46, 0xF0, 0xA6, 0x33, 0x2D, 0xA2,
	0xDC, 0x99, 0x57, 0x38, 0x59, 0xCF, 0x53, 0xFA, 0x3E, 0x78, 0x46, 0xA0,
	0xA9, 0x50, 0x12, 0x72, 0xAC, 0x15, 0xC6, 0xA7, 0x42, 0x0F, 0x59, 0x6E,
	0xEA, 0xB0, 0x3D, 0xB8, 0x94, 0x32, 0xD1, 0xB6, 0xE8, 0x90, 0x06, 0x66,
	0x0C, 0xDE, 0xA9, 0x35, 0xC7, 0xDD, 0x72, 0x42, 0x38, 0x33, 0x32, 0x2F,
	0x2C, 0x3F, 0xBD, 0x01, 0xD6, 0x47, 0xFC, 0x89, 0x31, 0x38, 0x2E, 0xB9,
	0x6B, 0xED, 0xDB, 0x85, 0x38, 0xB1, 0xA5, 0x50, 0xFA, 0xFB, 0xA7, 0x31,
	0xEC, 0xB6, 0xBB, 0x82, 0x50, 0xB4, 0x88, 0x5C, 0xED, 0xE5, 0x4B, 0x5B,
	0xBF, 0xB3, 0x18, 0xFB, 0xAD, 0x24, 0x41, 0x55, 0x80, 0xCD, 0xA3, 0xA1,
	0xD6, 0xD5, 0xB6, 0x06, 0xE9, 0x85, 0x12, 0x33, 0x52, 0x56, 0xF1, 0xB7,
	0xDC, 0x57, 0x9E, 0xB4, 0x00, 0x1E, 0xCB, 0x62, 0x13, 0x4C, 0x90, 0x9A,
	0x9D, 0x64, 0x80, 0xD1, 0x5E, 0xB3, 0xCB, 0x8A, 0x73, 0x4E, 0x7B, 0xBE,
	0x4D, 0xA7, 0xF7, 0xB7, 0x9C, 0x1C, 0x7F, 0x27, 0x1E, 0x7F, 0x58, 0xB2,
	0x74, 0xAF, 0x94, 0x0E, 0x19, 0x23, 0xE1, 0x6B, 0xD8, 0x20, 0x4F, 0x2C,
	0x13, 0xE8, 0x8C, 0x37, 0x46, 0x27, 0x55, 0x68, 0xDA, 0x3F, 0x7A, 0xC6,
	0xEF, 0x87, 0x1D, 0x3B, 0x95, 0x43, 0x5E, 0x75, 0xE0, 0x02, 0x22, 0x0E,
	0x11, 0x60, 0xAB, 0x1A, 0x91, 0x94, 0xC4, 0xFA, 0xD9, 0x92, 0x2B, 0xE5,
	0x03, 0xE0, 0x7A, 0x17, 0x5C, 0x67, 0x22, 0xB3, 0xCB, 0x77, 0x9E, 0x22,
	0x01, 0x5F, 0x5D, 0x64, 0xE4, 0x2F, 0xC4, 0x61, 0xCA, 0xC7, 0xFD, 0x20,
	0x24, 0x30, 0xAB, 0x3F, 0x1A, 0x08, 0x85, 0x08, 0x39, 0xDE, 0x19, 0x1C,
	0x1A, 0xEA, 0xB8, 0x7E, 0xE5, 0xBC, 0xD9, 0xB2, 0x59, 0xC8, 0x81, 0x02,
	0x1D, 0x5C, 0xC0, 0xDD, 0x8D, 0x56, 0xB6, 0x2E, 0x85, 0x26, 0xA8, 0x34,
	0x92, 0x36, 0x9A, 0x84, 0xBD, 0x27, 0xC1, 0x9D, 0x5E, 0x14, 0xC4, 0xB7,
	0x02, 0xA8, 0xC9, 0xC2, 0xAD, 0xDC, 0x98, 0x42, 0x51, 0xDE, 0x94, 0x28,
	0x39, 0xEF, 0xE9, 0x7F, 0x05, 0x3F, 0x1D, 0x67, 0x72, 0x04, 0xCF, 0x7D,
	0x38, 0x49, 0xC4, 0x59, 0xA5, 0xF6, 0xB6, 0x02, 0x31, 0xD0, 0x05, 0x74,
	0x4B, 0xD0, 0x89, 0xD1, 0x7F, 0xC6, 0xDB, 0x7E, 0x75, 0x62, 0xA3, 0xC2,
	0x2E, 0xB0, 0xCC, 0x9A, 0xD3, 0xA4, 0x14, 0xB6, 0xF2, 0x91, 0x44, 0x3F,
	0x84, 0xE0, 0x90, 0x4A, 0x6A, 0x34, 0x8C, 0x35, 0x3C, 0xB2, 0xA9, 0x35,
	0x88, 0xB0, 0x88, 0xF8, 0x7E, 0x5C, 0xD2, 0x08, 0x5E, 0x08, 0x15, 0x03,
	0xBC, 0xF5, 0x42, 0x6B, 0x28, 0xED, 0xDD, 0xAA, 0x4D, 0x78, 0x10, 0x31,
	0x32, 0xA2, 0xC5, 0xCA, 0xEE, 0x9A, 0x62, 0x52, 0x3E, 0x48, 0x83, 0xA4,
	0xCA, 0xD4, 0xC7, 0xA7, 0xA5, 0x3F, 0x44, 0x1C, 0x86, 0xAD, 0x52, 0x7D,
	0x80, 0x1D, 0x9E, 0x32, 0x3F, 0x2A, 0x2E, 0xD8, 0x89, 0xC1, 0xA4, 0xD6,
	0xC1, 0x90, 0x2E, 0x1A, 0x20, 0x4B, 0x87, 0x32, 0x35, 0x25, 0xD8, 0xB8,
	0x57, 0x15, 0x85, 0x1E, 0x3C, 0x8A, 0xDC, 0x1A, 0x49, 0x3D, 0x70, 0x35,
	0x99, 0xAA, 0xDE, 0x2C, 0xD4, 0xAF, 0x79, 0x72, 0xAB, 0x97, 0x84, 0x20,
	0xB6, 0x4F, 0x34, 0x3F, 0xEA, 0xAE, 0x5F, 0x8F, 0x3A, 0x42, 0xDB, 0x68,
	0xE5, 0x84, 0x63, 0x2E, 0x7A, 0x0E, 0xBD, 0x28, 0x6A, 0x24, 0xB6, 0xAB,
	0xE4, 0xAC, 0x20, 0x7C, 0x81, 0xD0, 0x69, 0x89, 0xF8, 0xDE, 0xA9, 0x02,
	0xFD, 0x1F, 0x08, 0xDA, 0x26, 0xC2, 0x24, 0xCA, 0xEB, 0x44, 0x16, 0x8D,
	0x55, 0x5F, 0xB9, 0xA9, 0x5A, 0x18, 0x50, 0xB1, 0x54, 0xF1, 0xBF, 0x06,
	0xC2, 0xB0, 0x95, 0xC2, 0xAE, 0xE5, 0xBF, 0xB3, 0xFD, 0xC9, 0xBF, 0x75,
	0x42, 0x7D, 0xA0, 0xA8, 0x95, 0xF9, 0x62, 0x3B, 0x9C, 0x0D, 0x81, 0xF3,
	0x9C, 0xFC, 0x19, 0x5B, 0xF7, 0xD1, 0x9C, 0xF0, 0xAA, 0xFE, 0xEF, 0x35,
	0x1E, 0x81, 0x9E, 0x02, 0x46, 0x52, 0x9B, 0x99, 0x0D, 0x12, 0x8B, 0x71,
	0x6C, 0x32, 0xB5, 0x23, 0x17, 0x03, 0xC5, 0xB0, 0xA1, 0xC3, 0x4B, 0x10,
	0x01, 0x4D, 0x4C, 0x4A, 0x46, 0x8F, 0xD9, 0x79, 0xBB, 0x10, 0x44, 0xB0,
	0x3C, 0x7D, 0x46, 0xFD, 0x38, 0xDF, 0xAF, 0x6E, 0x58, 0x7D, 0xE1, 0xEB,
	0xBB, 0x8C, 0xDC, 0x79, 0xDA, 0x41, 0xD1, 0x8B, 0x0B, 0x11, 0x4F, 0xE5,
	0x1C, 0xC1, 0x59, 0xA7, 0x1E, 0x5A, 0xC1, 0xEE, 0x27, 0x33, 0xC8, 0x55,
	0xA9, 0x32, 0xEA, 0xF7, 0x45, 0xB0, 0x08, 0xE9, 0x32, 0xDF, 0x70, 0x24,
	0x82, 0xD3, 0x2A, 0x3E, 0x4F, 0x42, 0xB9, 0x25, 0x10, 0xD1, 0x73, 0xFA,
	0xFD, 0xC1, 0x84, 0xF2, 0xF7, 0x0E, 0xBC, 0x9D, 0x90, 0x39, 0xD7, 0xFD,
	0x45, 0x77, 0xBA, 0x29, 0xF9, 0x87, 0x45, 0xC1, 0x32, 0x44, 0xB0, 0x27,
	0x6B, 0xFC, 0x8A, 0xFE, 0x00, 0x6F, 0x61, 0x98, 0xD0, 0x60, 0xC8, 0x10,
	0xE5, 0xBC, 0x88, 0x13, 0x45, 0x44, 0xA5, 0xEB, 0x6E, 0xCB, 0x11, 0xAF,
	0x30, 0xDC, 0x8B, 0xF8, 0x30, 0x46, 0xDA, 0x76, 0xF1, 0xE5, 0x14, 0x51,
	0x8A, 0x02, 0x5A, 0x5A, 0xAA, 0x7B, 0x2D, 0x57, 0x0A, 0x5C, 0x73, 0xD1,
	0x88, 0xCE, 0xBE, 0x3D, 0x06, 0x3F, 0x48, 0x1D, 0x44, 0x24, 0x6F, 0x4F,
	0x7F, 0x6A, 0xF2, 0x16, 0x34, 0x35, 0x38, 0x73, 0x8A, 0xE5, 0x25, 0xF4,
	0x34, 0x9E, 0x5B, 0x40, 0x90, 0x04, 0x57, 0x1B, 0x57, 0x75, 0x8F, 0xEA,
	0x1C, 0xF8, 0x7A, 0x68, 0x01, 0x1C, 0x8D, 0xBA, 0xF4, 0xE3, 0xD3, 0x8F,
	0x7F, 0xE4, 0x50, 0x35, 0x6B, 0x6B, 0xF6, 0xFC, 0x5F, 0x9B, 0x98, 0x78,
	0x16, 0x68, 0x72, 0x74, 0x71, 0x78, 0x25, 0x68, 0xE5, 0x1E, 0x66, 0xE2,
	0x4E, 0xC8, 0xDB, 0x92, 0x8E, 0x88, 0x64, 0x74, 0xDE, 0xDB, 0x85, 0x56,
	0x9F, 0xF9, 0xC4, 0x29, 0x54, 0xA8, 0xFB, 0xBA, 0xEA, 0xAB, 0xC7, 0x49,
	0x5C, 0x6C, 0xD7, 0x61, 0x8C, 0xE2, 0x2B, 0xF5, 0xA0, 0xA8, 0xD2, 0x41,
	0xC0, 0x54, 0xAB, 0xA7, 0x56, 0x5C, 0xE7, 0xA5, 0xEA, 0xBC, 0x47, 0xD1,
	0x0D, 0xD9, 0xC0, 0xA9, 0xC4, 0xA7, 0x3E, 0xD1, 0x2B, 0x1E, 0x34, 0x31,
	0x36, 0x9D, 0xB9, 0x51, 0xD3, 0xAD, 0x29, 0xE6, 0x9B, 0xD8, 0x4B, 0x93,
	0x33, 0x2F, 0x30, 0xEF, 0x18, 0x90, 0x69, 0x11, 0x09, 0xEA, 0xBA, 0xE0,
	0x10, 0x93, 0x63, 0x71, 0xA8, 0x83, 0x59, 0xDB, 0xFC, 0x12, 0x22, 0x84,
	0xC7, 0x01, 0x20, 0x99, 0xEC, 0x59, 0xA9, 0xE6, 0x9B, 0x5B, 0x8B, 0xB8,
	0x68, 0x52, 0x61, 0x8B, 0x4E, 0xF3, 0x50, 0x69, 0xF1, 0x49, 0x9B, 0xAF,
	0x53, 0xAD, 0xA0, 0x9D, 0x23, 0xE0, 0xE0, 0xC4, 0x31, 0xE4, 0x8E, 0x1C,
	0x51, 0x14, 0xFC, 0x95, 0x9C, 0xA6, 0x34, 0x85, 0xB0, 0x36, 0xFC, 0x7A,
	0x53, 0x03, 0x31, 0x0E, 0xCB, 0x34, 0x3E, 0xDF, 0xD1, 0x71, 0xBC, 0xDB,
	0xA1, 0xAF, 0x59, 0x4A, 0x03, 0x19, 0xA7, 0x8E, 0xB5, 0x82, 0x15, 0x24,
	0x69, 0x68, 0xBD, 0x9C, 0x2E, 0xFA, 0x06, 0xB5, 0x70, 0xC5, 0x70, 0xC4,
	0x14, 0x99, 0x01, 0x49, 0xBD, 0x6E, 0xAE, 0x10, 0xA1, 0xE4, 0xEF, 0xDD,
	0xE5, 0x51, 0x22, 0x9D, 0xF7, 0x93, 0xAB, 0x41, 0xBD, 0x86, 0x7A, 0xCC,
	0x51, 0x94, 0xEC, 0x22, 0xBE, 0x0D, 0x67, 0xFD, 0xA3, 0xFD, 0xCF, 0xF8,
	0x74, 0x0A, 0x5E, 0x1C, 0x71, 0xAD, 0xB6, 0xD0, 0xD7, 0xF8, 0x71, 0x34,
	0xAB, 0x62, 0xE7, 0xA8, 0x6B, 0x8F, 0x1E, 0x43, 0x46, 0xA5, 0xE4, 0xB4,
	0x52, 0x81, 0x66, 0xB3, 0xE5, 0x10, 0x23, 0x21, 0x2B, 0x31, 0x0F, 0xB8,
	0xB6, 0xC5, 0xA5, 0xC9, 0x90, 0x07, 0x83, 0xD0, 0xC3, 0x10, 0x7A, 0x04,
	0xBD, 0x8A, 0x3C, 0x7B, 0xF9, 0x0E, 0x51, 0x81, 0x96, 0xC8, 0xAE, 0xF9,
	0x27, 0xDE, 0x62, 0x7A, 0x41, 0x60, 0x35, 0x8F, 0x77, 0xBC, 0x95, 0x11,
	0x2C, 0xC4, 0x6C, 0x47, 0x7A, 0xEB, 0x29, 0xE5, 0x8E, 0xB5, 0xD6, 0xA5,
	0x54, 0x1B, 0xD0, 0xE0, 0x0F, 0x7D, 0x5C, 0x51, 0xD8, 0x6C, 0x92, 0x2F,
	0x13, 0x4E, 0x90, 0x77, 0xF8, 0x8D, 0x69, 0x78, 0x96, 0x96, 0x49, 0x9F,
	0x3C, 0x2E, 0x5C, 0xA6, 0x73, 0x27, 0x7D, 0xAD, 0x8D, 0xE3, 0x9B, 0x4A,
	0x2F, 0x50, 0x0A, 0x42, 0x7E, 0xF2, 0x3B, 0x50, 0x5C, 0x81, 0xC9, 0x49,
	0x01, 0x96, 0x83, 0x0A, 0xEC, 0x7F, 0xED, 0x1C, 0xA5, 0x7D, 0xF1, 0xE6,
	0xC4, 0xB3, 0x8F, 0xF9, 0x0F, 0xDB, 0x7B, 0xC1, 0x35, 0xF7, 0x63, 0x4A,
	0x39, 0xD4, 0x0E, 0x9E, 0x05, 0xD9, 0x42, 0xAA, 0xAB, 0x52, 0xCA, 0x4E,
	0x98, 0x3B, 0x43, 0x1A, 0x91, 0x25, 0xA9, 0x34, 0xD5, 0x66, 0xB2, 0xF4,
	0xFF, 0xDE, 0x64, 0x91, 0x90, 0xB9, 0x17, 0x70, 0xA0, 0xD6, 0xEA, 0xB6,
	0x36, 0xF4, 0x44, 0xCE, 0x86, 0x7B, 0x18, 0x74, 0x9C, 0x18, 0xAD, 0xB6,
	0xE0, 0x74, 0xC1, 0x0E, 0x29, 0x5D, 0x6A, 0x36, 0xD1, 0x3E, 0xB8, 0x2A,
	0xE4, 0x23, 0x1D, 0xB2, 0xAE, 0xF5, 0x5B, 0x8E, 0x2C, 0xD9, 0xD1, 0xE1,
	0x4F, 0x58, 0xA6, 0xE3, 0x88, 0x2E, 0xF9, 0xCF, 0x32, 0x3E, 0x8E, 0x37,
	0x95, 0xFF, 0xAD, 0x68, 0x11, 0x5E, 0x7F, 0x3D, 0x38, 0x06, 0x7C, 0x33,
	0x32, 0x78, 0x09, 0xEC, 0xCA, 0x3E, 0x08, 0xF1, 0xD0, 0x95, 0x19, 0xC9,
	0x7E, 0x62, 0xB2, 0x02, 0xA3, 0x5D, 0xF8, 0x3F, 0xA2, 0xB0, 0x8B, 0x38,
	0xB1, 0x8C, 0xEA, 0xB3, 0xE4, 0xBF, 0xD3, 0x6C, 0x6D, 0x3D, 0xD1, 0xC6,
	0xDA, 0x6B, 0x7A, 0xBA, 0x05, 0xEA, 0x9E, 0xA5, 0xE9, 0x00, 0xCC, 0x80,
	0x57, 0xAB, 0xD9, 0x0A, 0xD1, 0x00, 0x82, 0x2A, 0x51, 0x4B, 0xA2, 0x96,
	0xEB, 0x96, 0x14, 0xA8, 0x46, 0xDF, 0x1D, 0x48, 0xAE, 0xFA, 0x12, 0xA8,
	0x89, 0x8E, 0xEF, 0xBC, 0x3C, 0xA1, 0x6E, 0xDD, 0x90, 0x66, 0x2E, 0x56,
	0x6B, 0xF7, 0x1D, 0xF0, 0x46, 0x11, 0x4A, 0xA6, 0x07, 0x73, 0xC4, 0xE3,
	0x97, 0xFE, 0x7E, 0x22, 0x6F, 0x22, 0xB4, 0x6F, 0xB0, 0x32, 0x0A, 0x5E,
	0x85, 0x7E, 0x54, 0xB4, 0x24, 0xBD, 0x36, 0xA7, 0x94, 0xE7, 0x37, 0xFD,
	0x1A, 0xAF, 0xF4, 0x44, 0xB4, 0x35, 0x4F, 0xE0, 0x41, 0x0E, 0x7D, 0x73,
	0x29, 0x28, 0xDA, 0xAF, 0x69, 0xB2, 0xC5, 0xA7, 0x2A, 0x0A, 0xB5, 0x9C,
	0xC2, 0xAC, 0x5F, 0x59, 0x5C, 0xEE, 0x44, 0x49, 0x6F, 0x4F, 0x64, 0x43,
	0x6F, 0x43, 0x44, 0xAA, 0xA0, 0x4E, 0x94, 0x7C, 0x26, 0x5A, 0xF1, 0xD9,
	0xE6, 0x09, 0x80, 0x7A, 0x7D, 0x2E, 0xA2, 0xB9, 0x1A, 0x7A, 0x8F, 0x2A,
	0x97, 0x77, 0x23, 0xB4, 0x10, 0xAD, 0x20, 0x7B, 0xA3, 0x0F, 0xFD, 0x44,
	0x38, 0xAD, 0x94, 0x39, 0x88, 0x1C, 0xC4, 0xC8, 0xDF, 0xF1, 0x04, 0xA6,
	0x51, 0x5D, 0x54, 0x53, 0x60, 0xE4, 0x8A, 0x89, 0x4A, 0x9C, 0xE1, 0x68,
	0x4D, 0xFE, 0x69, 0x94, 0x0B, 0x8E, 0xED, 0x6C, 0xFE, 0x11, 0xA7, 0x77,
	0xBF, 0x08, 0x41, 0x67, 0x22, 0x59, 0x51, 0x48, 0xEE, 0x59, 0x02, 0x0E,
	0x60, 0x6D, 0xAE, 0x8C, 0xC6, 0x39, 0xB7, 0x55, 0xC5, 0x3B, 0x87, 0xA9,
	0xBD, 0xD8, 0xEA, 0x48, 0x21, 0xE4, 0x57, 0x51, 0x56, 0x03, 0xF4, 0xBE,
	0xBD, 0xBD, 0xC5, 0x26, 0x9B, 0x27, 0xE3, 0xAE, 0xD5, 0x1E, 0x30, 0xE9,
	0x7C, 0x9D, 0xDB, 0xE1, 0x09, 0x9D, 0x82, 0x49, 0x15, 0x38, 0x69, 0xFC,
	0x1D, 0x52, 0x1A, 0x75, 0xE6, 0xDD, 0x1D, 0xBE, 0x06, 0xC4, 0x9F, 0x14,
	0x4C, 0x12, 0xDE, 0xDF, 0x4A, 0xE1, 0x3B, 0xE7, 0xD1, 0xE3, 0x71, 0xD1,
	0xFA, 0xD8, 0x0E, 0x63, 0x27, 0xA9, 0xC7, 0x9D, 0xC0, 0x01, 0xC2, 0xDD,
	0xFC, 0xA6, 0x1F, 0x59, 0x87, 0xC5, 0x56, 0x99, 0x80, 0xEB, 0xF0, 0xB8,
	0xB3, 0x00, 0x9A, 0x61, 0xDB, 0x50, 0x79, 0x48, 0x37, 0x35, 0xDA, 0xD8,
	0xF2, 0x37, 0xA7, 0x43, 0xA7, 0xEB, 0x88, 0x2C, 0x68, 0xB4, 0xBB, 0x14,
	0x45, 0x31, 0x6B, 0x87, 0x65, 0xE7, 0x82, 0xB4, 0x74, 0xD2, 0xFF, 0x7F,
	0x60, 0x15, 0x94, 0x75, 0xEE, 0x30, 0x3C, 0x4E, 0xFC, 0x41, 0xD1, 0x5B,
	0xDD, 0x84, 0x6E, 0x13, 0x6C, 0xF8, 0x12, 0xE6, 0xB7, 0xA4, 0xB9, 0xC8,
	0x13, 0x89, 0x0C, 0x34, 0xA6, 0xAF, 0x09, 0xEB, 0xF2, 0xB3, 0x79, 0x77,
	0x80, 0xD8, 0x77, 0x64, 0xAD, 0x32, 0x3D, 0xD2, 0x06, 0xDF, 0x72, 0x11,
	0x4A, 0xA7, 0x70, 0xCE, 0xF9, 0xE6, 0x81, 0x35, 0xA4, 0xA7, 0x52, 0xB5,
	0x13, 0x68, 0x5C, 0x69, 0x45, 0xE2, 0x77, 0x2D, 0xBE, 0x2C, 0xE9, 0x38,
	0x25, 0x28, 0x7B, 0x63, 0x2C, 0x19, 0x8F, 0x59
};

/* aad */
uint8_t aad[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B
};

/* iv */
uint8_t iv[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
	0x0C, 0x0D, 0x0E, 0x0F
};

/* cipher key */
uint8_t cipher_key[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
	0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
	0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
};

/* auth key */
uint8_t auth_key[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
	0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
	0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23,
	0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
	0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
	0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53,
	0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B,
	0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
	0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F
};

/* Digests */
uint8_t digest[2048] = { 0x00 };

struct cperf_test_vector*
cperf_test_vector_get_dummy(struct cperf_options *options)
{
	struct cperf_test_vector *t_vec;

	t_vec = (struct cperf_test_vector *)rte_malloc(NULL,
			sizeof(struct cperf_test_vector), 0);
	if (t_vec == NULL)
		return t_vec;

	t_vec->plaintext.data = plaintext;
	t_vec->plaintext.length = options->max_buffer_size;

	if (options->op_type ==	CPERF_CIPHER_ONLY ||
			options->op_type == CPERF_CIPHER_THEN_AUTH ||
			options->op_type == CPERF_AUTH_THEN_CIPHER ||
			options->op_type == CPERF_AEAD) {
		if (options->cipher_algo == RTE_CRYPTO_CIPHER_NULL) {
			t_vec->cipher_key.length = 0;
			t_vec->ciphertext.data = plaintext;
			t_vec->cipher_key.data = NULL;
			t_vec->cipher_iv.data = NULL;
		} else {
			t_vec->cipher_key.length = options->cipher_key_sz;
			t_vec->ciphertext.data = ciphertext;
			t_vec->cipher_key.data = cipher_key;
			t_vec->cipher_iv.data = rte_malloc(NULL, options->cipher_iv_sz,
					16);
			if (t_vec->cipher_iv.data == NULL) {
				rte_free(t_vec);
				return NULL;
			}
			memcpy(t_vec->cipher_iv.data, iv, options->cipher_iv_sz);
		}
		t_vec->ciphertext.length = options->max_buffer_size;

		/* Set IV parameters */
		t_vec->cipher_iv.data = rte_malloc(NULL, options->cipher_iv_sz,
				16);
		if (options->cipher_iv_sz && t_vec->cipher_iv.data == NULL) {
			rte_free(t_vec);
			return NULL;
		}
		memcpy(t_vec->cipher_iv.data, iv, options->cipher_iv_sz);
		t_vec->cipher_iv.length = options->cipher_iv_sz;

		t_vec->data.cipher_offset = 0;
		t_vec->data.cipher_length = options->max_buffer_size;

	}

	if (options->op_type ==	CPERF_AUTH_ONLY ||
			options->op_type == CPERF_CIPHER_THEN_AUTH ||
			options->op_type == CPERF_AUTH_THEN_CIPHER ||
			options->op_type == CPERF_AEAD) {
		uint8_t aad_alloc = 0;

		t_vec->auth_key.length = options->auth_key_sz;

		switch (options->auth_algo) {
		case RTE_CRYPTO_AUTH_NULL:
			t_vec->auth_key.data = NULL;
			aad_alloc = 0;
			break;
		case RTE_CRYPTO_AUTH_AES_GCM:
			t_vec->auth_key.data = NULL;
			aad_alloc = 1;
			break;
		case RTE_CRYPTO_AUTH_SNOW3G_UIA2:
		case RTE_CRYPTO_AUTH_KASUMI_F9:
		case RTE_CRYPTO_AUTH_ZUC_EIA3:
			t_vec->auth_key.data = auth_key;
			aad_alloc = 1;
			break;
		case RTE_CRYPTO_AUTH_AES_GMAC:
			/* auth key should be the same as cipher key */
			t_vec->auth_key.data = cipher_key;
			aad_alloc = 1;
			break;
		default:
			t_vec->auth_key.data = auth_key;
			aad_alloc = 0;
			break;
		}

		if (aad_alloc && options->auth_aad_sz) {
			t_vec->aad.data = rte_malloc(NULL,
					options->auth_aad_sz, 16);
			if (t_vec->aad.data == NULL) {
				if (options->op_type !=	CPERF_AUTH_ONLY)
					rte_free(t_vec->cipher_iv.data);
				rte_free(t_vec);
				return NULL;
			}
			memcpy(t_vec->aad.data, aad, options->auth_aad_sz);
		} else {
			t_vec->aad.data = NULL;
		}

		/* Set IV parameters */
		t_vec->auth_iv.data = rte_malloc(NULL, options->auth_iv_sz,
				16);
		if (options->auth_iv_sz && t_vec->auth_iv.data == NULL) {
			if (options->op_type != CPERF_AUTH_ONLY)
				rte_free(t_vec->cipher_iv.data);
			rte_free(t_vec);
			return NULL;
		}
		memcpy(t_vec->auth_iv.data, iv, options->auth_iv_sz);
		t_vec->auth_iv.length = options->auth_iv_sz;

		t_vec->aad.phys_addr = rte_malloc_virt2phy(t_vec->aad.data);
		t_vec->aad.length = options->auth_aad_sz;
		t_vec->digest.data = rte_malloc(NULL, options->auth_digest_sz,
				16);
		if (t_vec->digest.data == NULL) {
			if (options->op_type !=	CPERF_AUTH_ONLY)
				rte_free(t_vec->cipher_iv.data);
			rte_free(t_vec->auth_iv.data);
			rte_free(t_vec->aad.data);
			rte_free(t_vec);
			return NULL;
		}
		t_vec->digest.phys_addr =
				rte_malloc_virt2phy(t_vec->digest.data);
		t_vec->digest.length = options->auth_digest_sz;
		memcpy(t_vec->digest.data, digest, options->auth_digest_sz);
		t_vec->data.auth_offset = 0;
		t_vec->data.auth_length = options->max_buffer_size;
	}

	return t_vec;
}
