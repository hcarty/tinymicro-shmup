#include "Mob.h"

void Mob::OnCreate()
{
  orxConfig_SetBool("IsMob", orxTRUE);

  // Get a movement speed specific to this mob
  auto speed = orxConfig_GetFloat("Speed");
  PushConfigSection(orxTRUE);
  orxConfig_SetFloat("Speed", speed);
  PopConfigSection();
}

void Mob::OnDelete()
{
}

orxBOOL Mob::OnCollide(ScrollObject *_poCollider, orxBODY_PART *_pstPart, orxBODY_PART *_pstColliderPart, const orxVECTOR &_rvPosition, const orxVECTOR &_rvNormal)
{
  if (orxString_Compare(orxBody_GetPartName(_pstColliderPart), "AttackProjectileBodyPart") == 0)
  {
    SetLifeTime(0.0);
  }

  return orxTRUE;
}

void Mob::Update(const orxCLOCK_INFO &_rstInfo)
{
  orxAABOX frustum;
  auto camera = orxCamera_Get("MainCamera");
  orxASSERT(camera);
  orxCamera_GetFrustum(camera, &frustum);

  orxVECTOR position;
  GetPosition(position, orxTRUE);

  if (!orxAABox_IsInside(&frustum, &position))
  {
    // Disappear once we're outside of the camera viewport
    SetLifeTime(0);
  }
}
