# 보스 AI 만들기
## 목표
- 간단하게 다크 소울, 검은 신화 손오공과 같이 보스 AI 만들기<br/>
![DarkSoul](https://github.com/user-attachments/assets/ec6ad2b1-ad2b-46b2-9ddb-333a01a90802)<dr/>
![wukong](https://github.com/user-attachments/assets/ea095227-5727-4a80-8e9b-6583b6f706d3)

### 구성도
![image](https://github.com/user-attachments/assets/1ec61ef8-9594-451e-b101-f9ebff2f35e9)
<br/>
AI가 Perception Component를 이용하여 Player를 감지하고 사이의 거리에 따라 행동을 나누었습니다. <br/>

### AI
![image](https://github.com/user-attachments/assets/1974fce7-4bcc-41ac-ae51-6f8538ea7f64)
<br/>
게임 파라곤의 캐릭터 손오공을 사용하였으며, Component와 AI Controller 등등 이용하여 플레이어 판별하고 공격하게 만들었습니다.

### BehaviorTree
#### 전체적 구도
![image](https://github.com/user-attachments/assets/13ba57fa-aff2-4756-a852-655f893e225d)<br/>
플레이어 발견 시와 발견 하지 못 하였을 시 두 가지로 나뉘어 실행되게 하였습니다.<br/>

#### Hitted And NoPlayer
![image](https://github.com/user-attachments/assets/510d92cf-4ed9-4569-a4da-e8531a86e75e)<br/>
AI가 플레이어에게 피격 당했을 때와 플레이어를 발견 하지 못 하였을 때 입니다.<br/>

#### SetPlayer
![image](https://github.com/user-attachments/assets/b1061658-d46d-41f7-bd60-f72f3fb13997)<br/>
AI가 플레이어를 발견 했을 때 입니다.<br/>
AI와 플레이어의 위치에 따라 Blackboard에 값을 다르게 저장하였습니다.<br/>

#### Approch
![image](https://github.com/user-attachments/assets/786bee9f-b4b1-4893-92a5-45319d57f30a)<br/>
플레이어가 AI의 시야각에 들어왔을 시 행하는 행동이며, AI가 플레이어를 따라 가게 만들었습니다.<br/>

#### Special Attack
플레이어와 사이가 일정 거리가 되면 행하는 행동이며, 두 번의 공격을 합니다.<br/>
첫 번째 공격은 여의봉을 길게 하여 플레이어를 밀어냅니다.<br/>
![image](https://github.com/user-attachments/assets/587c30ce-f3d0-4e8f-b49e-5878cb3c9abc)<br/>


이때 피격당한 플레이어는 잠시 Stun 상태가 됩니다.<br/>
![image](https://github.com/user-attachments/assets/fc36e7dd-f60c-41e8-b4e5-fc6be03cae83)<br/>

두 번째 공격은 Stun 상태인 플레이어를 향해 점프를 하여 여의봉을 내려 찍습니다.<br/>
![image](https://github.com/user-attachments/assets/381e9fd9-3f9d-4ab0-9c7b-ccb132a8b07a)
![image](https://github.com/user-attachments/assets/57098ce5-33c1-4a82-beb3-f185b7c29cf4)

#### Attack
플레이어에게 근접했을때 행하는 행동이며, AI가 플레이어를 공격합니다.<br/>
총 3번의 공격을 행하며, 행하는 동안 플레이어를 집중합니다.<br/>


