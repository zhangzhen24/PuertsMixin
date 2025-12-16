import * as UE from "ue";
import mixin from "{MixinImportPath}";

// 蓝图类路径（Puerts绑定路径）
const AssetPath = "{AssetPath}";

// 创建一个继承 TS 类（或其他类）的接口（用于类型提示）
export interface {BPName}

extends
{TsTypePath}
{}

// 创建一个继承 TS 的本体类，并通过 mixin 将蓝图逻辑混入
@mixin(AssetPath)
export class {BPName}

implements
{TsTypePath}
{

	test
}
