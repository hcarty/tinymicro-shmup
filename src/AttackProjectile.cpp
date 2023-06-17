#include "AttackProjectile.h"

void AttackProjectile::OnCreate()
{
  orxConfig_SetBool("IsAttackProjectile", orxTRUE);
}

void AttackProjectile::OnDelete()
{
}

orxBOOL AttackProjectile::OnCollide(ScrollObject *_poCollider, orxBODY_PART *_pstPart, orxBODY_PART *_pstColliderPart, const orxVECTOR &_rvPosition, const orxVECTOR &_rvNormal)
{
  if (orxString_Compare(orxBody_GetPartName(_pstColliderPart), "MobBodyPart") == 0)
  {
    SetLifeTime(0.0);
    orxCOMMAND_VAR _result;
    orxCommand_Evaluate("Game.AddScore 1", &_result);
  }

  return orxTRUE;
}

void AttackProjectile::Update(const orxCLOCK_INFO &_rstInfo)
{
}
