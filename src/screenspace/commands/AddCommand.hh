// Copyright 2019 Edward Hoyle
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SCREENSPACE_ADDCOMMAND_HH
#define SCREENSPACE_ADDCOMMAND_HH

#include <maya/MPxCommand.h>
#include <maya/MSyntax.h>

namespace screenspace {

class AddCommand : public MPxCommand {
public:
  static MString typeName;
  static void* creator();
  static MSyntax createSyntax();
public:
  virtual MStatus doIt(const MArgList& args);
};

}
#endif // SCREENSPACE_ADDCOMMAND_HH
