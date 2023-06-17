#pragma once

#include "Object.h"

class AttackProjectile : public Object
{
public:
protected:
  void OnCreate();
  void OnDelete();
  orxBOOL OnCollide(ScrollObject *_poCollider, orxBODY_PART *_pstPart, orxBODY_PART *_pstColliderPart, const orxVECTOR &_rvPosition, const orxVECTOR &_rvNormal);
  void Update(const orxCLOCK_INFO &_rstInfo);

private:
};
