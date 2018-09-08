#include "GameObject.hpp"

namespace ay{
  class GUIObject : public GameObject{
  };

  //some useful defaults:

  class GUIExit : GUIObject{
  };

  class GUIMultChoice : GUIObject{
  };

  class GUIToggle : GUIObject{
  };
}
