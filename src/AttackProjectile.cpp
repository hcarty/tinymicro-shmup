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
  orxASSERT(_poCollider, "Collision with non-ScrollObject");

  SetLifeTime(0.0);

  _poCollider->PushConfigSection();
  if (orxConfig_HasValue("OnDestruction"))
  {
    orxCOMMAND_VAR _result;
    orxCommand_Evaluate(orxConfig_GetString("OnDestruction"), &_result);
  }
  _poCollider->PopConfigSection();

  return orxTRUE;
}

void AttackProjectile::Update(const orxCLOCK_INFO &_rstInfo)
{
}
