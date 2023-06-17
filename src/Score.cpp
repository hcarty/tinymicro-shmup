#include "Score.h"

namespace
{
  void PushConfigRuntime()
  {
    orxConfig_PushSection("Runtime");
  }

  void PopConfigRuntime()
  {
    orxConfig_PopSection();
  }

  orxS32 GetScore()
  {
    PushConfigRuntime();
    auto score = orxConfig_GetS32("Score");
    PopConfigRuntime();
    return score;
  }

  orxBOOL GetGameOver()
  {
    PushConfigRuntime();
    auto gameOver = orxConfig_GetBool("GameOver");
    PopConfigRuntime();
    return gameOver;
  }

  void SetScore(orxS32 score)
  {
    PushConfigRuntime();
    orxConfig_SetS32("Score", score);
    PopConfigRuntime();
  }

  orxS32 AddScore(orxS32 diff)
  {
    auto score = GetScore();
    score += diff;
    if (score < 0)
    {
      score = 0;
    }
    SetScore(score);
    return score;
  }

  void orxFASTCALL AddScoreCommand(orxU32 _u32ArgNumber, const orxCOMMAND_VAR *_astArgList, orxCOMMAND_VAR *_pstResult)
  {
    /* Updates result */
    _pstResult->s32Value = AddScore(_astArgList[0].s32Value);

    /* Done! */
    return;
  }

  void registerCommands()
  {
    orxCOMMAND_REGISTER("Game.AddScore", AddScoreCommand, "UpdatedScore", orxCOMMAND_VAR_TYPE_S32, 1, 0, {"Diff", orxCOMMAND_VAR_TYPE_S32});
  }

  void unregisterCommands()
  {
    orxCOMMAND_UNREGISTER("Game.AddScore");
  }
}

void Score::OnCreate()
{
  orxConfig_SetBool("IsScore", orxTRUE);
  registerCommands();
}

void Score::OnDelete()
{
  unregisterCommands();
}

void Score::Update(const orxCLOCK_INFO &_rstInfo)
{
  auto score = GetScore();

  // Update the text to match the current score
  const size_t MAX_LABEL_LENGTH = 32;
  orxCHAR label[MAX_LABEL_LENGTH] = "";
  orxString_NPrint(label, MAX_LABEL_LENGTH, "Score: %d", score);
  orxObject_SetTextString(GetOrxObject(), label);

  Object::Update(_rstInfo);
}
