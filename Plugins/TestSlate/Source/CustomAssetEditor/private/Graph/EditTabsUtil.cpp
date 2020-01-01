#include "EditTabsUtil.h"

const FName FScenarioEditorTabsUtil::GraphDetailsID(TEXT("ScenarioEditor_Properties"));
const FName FScenarioEditorTabsUtil::SearchID(TEXT("ScenarioEditor_Search"));

const FName FScenarioEditorTabsUtil::GraphEditorID(TEXT("Document"));

/* 节点相关 */
const FName FScenarioNodeUtil::NodeCategoryNormal(TEXT("NormalBase"));
const FName FScenarioNodeUtil::NodeCategoryRoot(TEXT("NormalRoot"));
const FName FScenarioNodeUtil::NodeCategoryEnd(TEXT("NormalEND"));
const FName FScenarioNodeUtil::NodeCategoryAssembly(TEXT("NodeAssembly"));
const FName FScenarioNodeUtil::NodeCategoryAction(TEXT("NodeAction"));

//PIN相关
const FName FScenarioPinUtil::SubPinCategoryRoot(TEXT("SubRoot"));
const FName FScenarioPinUtil::SubPinCategoryEnd(TEXT("SubEnd"));
const FName FScenarioPinUtil::PinCategoryNotAllow(TEXT("NotAllowPin"));
const FName FScenarioPinUtil::PinCategoryNormal(TEXT("NormalBase"));
const FName FScenarioPinUtil::PinCategoryMulti(TEXT("NormalMulti"));

//控制器相关
const FName FControllerCategoryUtil::ControllerBase(TEXT("ControllerBase"));
const FName FControllerCategoryUtil::ControllerAction(TEXT("ControllerAction"));


