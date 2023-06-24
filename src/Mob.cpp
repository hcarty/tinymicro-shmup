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

void Mob::OnCollide(ScrollObject *_poCollider, orxBODY_PART *_pstPart, orxBODY_PART *_pstColliderPart, const orxVECTOR &_rvPosition, const orxVECTOR &_rvNormal)
{
  if (orxString_SearchString(orxBody_GetPartName(_pstColliderPart), "AttackProjectileBodyPart") != orxNULL)
  {
    SetLifeTime(0.0);
  }
}

void Mob::Update(const orxCLOCK_INFO &_rstInfo)
{
  orxAABOX frustum;
  auto camera = orxCamera_Get("MainCamera");
  orxASSERT(camera);
  orxCamera_GetFrustum(camera, &frustum);

  orxVECTOR position;
  GetPosition(position, orxTRUE);
  auto surviving = GetLifeTime() < 0;
  auto inside = orxAABox_IsInside(&frustum, &position);

  if (surviving && !inside)
  {
    // Disappear shortly after we leave the camera viewport
    SetLifeTime(2);
  }
  else if (!surviving && inside)
  {
    // Reset lifetime in case we leave and then re-enter the viewport
    SetLifeTime(-1);
  }
}
