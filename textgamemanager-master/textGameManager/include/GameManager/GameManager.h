// GameManager.h
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <vector>
#include "tinyxml2.h"
#include "World/Room.h"  // Room 클래스의 경로가 World 폴더에 있으므로 경로에 맞게 수정
#include "Entities/Player.h"  // Player 클래스의 경로
#include "MonsterFactory.h"  // 몬스터 팩토리 헤더 경로 수정
#include "Events/Event.h"  // Event 클래스 헤더 추가로 로드
#include "InputManager.h"  // InputManager 헤더 추가

using namespace tinyxml2;

class GameManager {
public:
    static GameManager& getInstance();  // 싱글톤 패턴을 위한 함수
    void initializeGame();  // 게임 초기화
    void startGame();  // 게임 시작
    void gameLoop();  // 게임 메인 루프
    void displayOptions(const std::vector<std::string>& options);  // 옵션 표시
    void startCombat(BaseMonster& enemy);   // 전투 시작
    void saveGame(const std::string& saveFileName); // 수정된 부분
    void loadGame(const std::string& loadFileName);  // 게임 불러오기
    Event loadEvent(const std::string& eventId);  // 이벤트 로드
    void displayMessage(const std::string& message);  // 메시지 표시
    void displayPlayerStatus();  // 플레이어 스테이터스 표시
    bool deleteSaveFile(const std::string& saveFileName);
    void displaySaveFiles();
    void useAbility();
    void managePlayerAbilityUsage();

private:
    GameManager(); // private 생성자
    ~GameManager() = default;
    GameManager(const GameManager&) = delete;  // 복사 생성자 삭제
    GameManager& operator=(const GameManager&) = delete;  // 복사 할당자 삭제

    Player player;  // 플레이어 객체
    std::vector<Room> worldMap;  // 월드 맵에 있는 방 리스트
    std::vector<Room> createWorldMap();  // 월드 맵 생성 함수
};

#endif // GAMEMANAGER_H