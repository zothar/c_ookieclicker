#include <memory>
#include <experimental/filesystem>
#include "gtest/gtest.h"
#include "GameLoop.h"
#include "Save.h"

struct SaveTestSuite : public ::testing::Test
{
    std::unique_ptr<Gameloop> game;
    int format1 = 1;
    std::experimental::filesystem::path current_source_file = std::experimental::filesystem::path(__FILE__);
    std::string testSaveFileFolder = current_source_file.parent_path().string() + "/data/";
    SaveTestSuite()
    {
        game = std::make_unique<Gameloop>(false);
    }
};

TEST_F(SaveTestSuite, saveBlankFile)
{
    //arrange
    auto saveFile = testSaveFileFolder + "saveBlankFile.save";
    //game->getWallet().incrementCookieAmount(CookieNumber(3));
    //game->getWallet().incrementCps(CookieNumber(20));
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    //game->incrementCookiesOnTime();
    auto savegame = Save(saveFile, game->getInventory(), game->getWallet(), format1);
    //act
    auto result = savegame.save();
    //assert
    ASSERT_EQ(std::experimental::filesystem::exists(saveFile), true);
    ASSERT_EQ(result, true);
}

TEST_F(SaveTestSuite, loadNonExistentFile)
{
    //arrange
    auto saveFile = testSaveFileFolder + "nonExistentFile.save";
    auto savegame = Save(saveFile, game->getInventory(), game->getWallet(), format1);
    // act
    auto result = savegame.load();
    //assert
    ASSERT_EQ(std::experimental::filesystem::exists(saveFile), false);
    ASSERT_EQ(result, false);
}

TEST_F(SaveTestSuite, saveThenLoad)
{
    //arrange
    auto saveFile = testSaveFileFolder + "saveThenLoad.save";
    auto key = game->getStore().getItemByName("Key");

    //act
    game->getWallet().incrementCookieAmount(CookieNumber(3));
    game->getWallet().incrementCps(CookieNumber(20));
    game->getInventory().addItem(key, 3);

    auto savegame = Save(saveFile, game->getInventory(), game->getWallet(), format1);
    auto saveResult = savegame.save();

    game->reset();

    auto loadResult = savegame.load();
    auto key2 = game->getStore().getItemByName("Key");
    //assert
    ASSERT_EQ(std::experimental::filesystem::exists(saveFile), true);
    ASSERT_EQ(saveResult, true);
    ASSERT_EQ(loadResult, true);
    ASSERT_EQ(game->getWallet().getTotalcookies(), 3);
    ASSERT_EQ(game->getWallet().getCps(), 20);
    ASSERT_EQ(game->getInventory().getItemCount(key2), 3);
}