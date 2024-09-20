#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

// fonts
const string kArialFont = "assets/fonts/arial.ttf";
const string kMineFont = "assets/fonts/mine.ttf";
const string kPixelBloatedFont = "assets/fonts/pixel_bloated.ttf";

// images
const string kFlagImage = "assets/images/flag.png";
const string kLoadingBarImage = "assets/images/loading_bar.png";
const string kDinoLoadingImage = "assets/images/dino_loading.png";
const string kBgBlackImage = "assets/images/bg_black.png";
const string kBgGameOverImage = "assets/images/bg_gameover.png";
const string kBgGameImage = "assets/images/bg_game.png";
const string kBgWelcomeImage = "assets/images/bg_welcome.jpg";
const string kDinoR0Image = "assets/images/dinoR0.png";
const string kDinoL0Image = "assets/images/dinoL0.png";
const string kMeteoroImage = "assets/images/meteoro.png";

// sounds
const string kClickSound = "assets/sounds/click.wav";
const string kCollisionSound = "assets/sounds/collision.wav";
const string kGameOverSound = "assets/sounds/game_over.wav";
const string kWelcomeSound = "assets/sounds/welcome.wav";

class ResourcesUtil
{
private:
    inline static map<string, Font> fonts;
    inline static map<string, SoundBuffer> sound_buffers;
    inline static map<string, Sound> sounds;
    inline static map<string, Texture> textures;
    inline static map<string, Sprite> sprites;

public:
    static Font &getFont(string fontName);
    static Sound &getSound(string soundName);
    static Sprite &getSprite(string spriteName);
    static Texture &getTexture(string textureName);
};
