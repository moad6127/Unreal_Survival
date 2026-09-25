# Unreal_Survival

Unreal엔진을 사용해서 기본적인 Survival 형태의 게임을 제작해보기     
Survival형태에 맞는 Map을 제작하고, 인벤토리를 구성한후 제작 시스템을 만들어 인벤토리 아이템을 사용해 제작할수 있도록 만들었다.      
또한 Map의 나무들을 공격하면 자를수 있도록 만들어서 재료들을 얻을수 있도록 만들었으며, 획득한 재료들을 사용해서 기지를 구축할수 있도록 BuildingSystem을 만들었다.      

Udemy의 *Build a multiplayer survival framework using Blueprints, networking, and modular design in Unreal Engine 5.* 강의를 활용하면서 제작했으며
블루프린트 로직/UI를 분석하여 코어 로직 및 시스템 구조를 C++로 모듈화 및 리팩토링했습니다.     


<img width="1938" height="1058" alt="Image" src="https://github.com/user-attachments/assets/ab041926-fd6a-4550-a398-47b7689ec3ac" />

<details><summary> 구분</summary>
<p>  
   
 * [Map](#Map)

 * [Inventory](#Inventory)

 * [Crafting](#Crafting)

 * [BuildingSystem](#BuildingSystem)

 * [Animal AI](#AnimalAI)

</p>
</details>
<br/> <br>   

  ## Map

<img width="1920" height="1008" alt="Image" src="https://github.com/user-attachments/assets/e3cb0faa-1e69-449f-a24e-3bde4f1a4d87" />

> Heightmap 기반 지형 생성: 외부 하이트맵 데이터를 입혀 절차적이고 자연스러운 대형 월드 지형의 기반을 구축했습니다.

> 자동 지형 머티리얼(Auto Landscape Material): 지형의 높이(Height)와 경사도(Slope) 데이터를 기반으로 텍스처가 자동으로 블렌딩되는 머티리얼을 제작해 자연스러운 환경 연출을 구현했습니다.     

  ### World

<img width="1903" height="874" alt="Image" src="https://github.com/user-attachments/assets/195f25ac-99a8-4a7e-a2d2-042ff244fa44" />

> *머티리얼 인스턴스(Material Instance) 기반 모듈화*: 파라미터화된 머티리얼 인스턴스를 활용해 재컴파일 없이 실시간으로 지형 텍스처 및 매핑 기준을 조정할 수 있도록 구성했습니다.

*  높이 및 경사도 연산 매핑:

    * *Height-based Texturing* : 고도에 따라 평지, 풀밭, 바위산, 눈 등의 텍스처가 자연스럽게 전환되도록 제어.

    * *Slope-based Texturing* : 절벽이나 급경사 구간에는 바위 텍스처가 자동으로 적용되어 수작업 페인팅 노력을 최소화.


  ### environment








  
  ## Inventory
  
  ### Item
  ### Equipmemt

  ## Crafting

  ## BuildingSystem

  ## AnimalAI
  
