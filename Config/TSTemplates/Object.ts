import * as UE from 'ue';
import mixin, { iMixinedClass } from '{MixinImportPath}';

const AssetPath = '{AssetPath}';

export interface {MixinName} extends {TsTypePath} {}

/** {BPName} Mixin */
@mixin(AssetPath, true, true)
export class {MixinName} extends iMixinedClass implements {MixinName} {
}
