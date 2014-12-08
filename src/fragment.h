//
// Tizen C++ SDK
// Copyright (c) 2012-2013 Samsung Electronics Co., Ltd.
//
// Licensed under the Flora License, Version 1.1 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://floralicense.org/license/
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef _FRAGMENT_H_
#define _FRAGMENT_H_

static const char* FRAGMENT_TEXT =
	"#ifdef GL_ES\n"
	"precision highp float;\n"
	"#endif\n"
	"\n"
	"varying vec4 v_color;\n"
	"\n"
	"void main (void)\n"
	"{\n"
	"    gl_FragColor = v_color;\n"
	"}";

#endif //_FRAGMENT_H_
