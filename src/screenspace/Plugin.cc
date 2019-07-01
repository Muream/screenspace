#include "screenspace/Log.hh"
#include "screenspace/PickerShape.hh"
#include "screenspace/PickerDrawOverride.hh"
#include "screenspace/commands/AddCommand.hh"
#include "screenspace/commands/RemoveCommand.hh"

#include "screenspace/CustomShape.hh"
#include "screenspace/CustomGeometryOverride.hh"

#include <maya/MGlobal.h>
#include <maya/MFnPlugin.h>
#include <maya/MDrawRegistry.h>

using namespace screenspace;

static const MString AEpickerTemplate = R"(global proc AEpickerTemplate(string $nodeName)
{
  editorTemplate -beginScrollLayout;
  editorTemplate -beginLayout "Geometry" -collapse 0;
  editorTemplate -addControl -label "Shape" "shape" "swapShape";
  editorTemplate -addControl "size";
  editorTemplate -addControl "width";
  editorTemplate -addControl "height";
  editorTemplate -addControl "color";
  editorTemplate -addControl "opacity";
  editorTemplate -addSeparator;
  editorTemplate -addControl "position";
  editorTemplate -addControl "offset";
  editorTemplate -addControl "verticalAlign";
  editorTemplate -addControl "horizontalAlign";
  editorTemplate -addControl "depth";
  editorTemplate -endLayout;
  editorTemplate -addExtraControls;
  editorTemplate -endScrollLayout;
})";

MStatus initializePlugin(MObject obj) {
  MFnPlugin plugin(obj, "Eddie Hoyle", "1.0", "Any");

  MStatus status;
  status = plugin.registerNode(PickerShape::typeName,
                               PickerShape::id,
                               &PickerShape::creator,
                               &PickerShape::initialize,
                               MPxNode::kSurfaceShape,
                               &PickerDrawOverride::classifcation);
  CHECK_MSTATUS(status);


  status = MHWRender::MDrawRegistry::registerDrawOverrideCreator(
      PickerDrawOverride::classifcation,
      PickerDrawOverride::id,
      PickerDrawOverride::creator);
  CHECK_MSTATUS(status);

  // ---------------------------------------------------------------------------

  status = plugin.registerNode(CustomShape::typeName,
                               CustomShape::id,
                               &CustomShape::creator,
                               &CustomShape::initialize,
                               MPxNode::kSurfaceShape,
                               &CustomGeometryOverride::classifcation);
  CHECK_MSTATUS(status);

  status = MHWRender::MDrawRegistry::registerGeometryOverrideCreator(
      CustomGeometryOverride::classifcation,
      CustomGeometryOverride::id,
      CustomGeometryOverride::creator);
  CHECK_MSTATUS(status);

  // ---------------------------------------------------------------------------

  status = plugin.registerCommand(AddCommand::typeName,
                                  AddCommand::creator,
                                  AddCommand::createSyntax);
  CHECK_MSTATUS(status);

  status = plugin.registerCommand(RemoveCommand::typeName,
                                  RemoveCommand::creator,
                                  RemoveCommand::createSyntax);
  CHECK_MSTATUS(status);

//  MGlobal::executeCommandOnIdle(AEpickerTemplate);
  return status;
}

MStatus uninitializePlugin(MObject obj) {
  MFnPlugin plugin(obj);
  MStatus status;

  status = plugin.deregisterNode(PickerShape::id);
  CHECK_MSTATUS(status);

  status = plugin.deregisterCommand(AddCommand::typeName);
  CHECK_MSTATUS(status);

  status = plugin.deregisterCommand(RemoveCommand::typeName);
  CHECK_MSTATUS(status);

  return status;
}