import * as UE from 'ue';
import mixin, { iMixinedClass } from '{MixinImportPath}';

const AssetPath = '{AssetPath}';

export interface {MixinName} extends {TsTypePath} {}

/** {BPName} Mixin */
@mixin(AssetPath, true, true)
export class {MixinName} extends iMixinedClass implements {MixinName} {

    ReceiveActivationAI(OwnerController: UE.AIController, ControlledPawn: UE.Pawn): void {}

    ReceiveTickAI(OwnerController: UE.AIController, ControlledPawn: UE.Pawn, DeltaSeconds: number): void {}

    ReceiveDeactivationAI(OwnerController: UE.AIController, ControlledPawn: UE.Pawn): void {}
}
