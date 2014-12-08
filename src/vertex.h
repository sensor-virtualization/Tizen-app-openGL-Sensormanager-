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

#ifndef _VERTEX_H_
#define _VERTEX_H_

static const char* VERTEX_TEXT =
	"uniform mat4 u_mvpMatrix;\n"
	"attribute vec4 a_position;\n"
	"attribute vec4 a_color;\n"
	"varying vec4 v_color;\n"
	"\n"
	"void main()\n"
	"{\n"
	"    v_color = a_color;\n"
	"    gl_Position = u_mvpMatrix * a_position;\n"
	"}                                                ";

#endif // _VERTEX_H_
