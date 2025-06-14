[![MSBuild](https://github.com/jabdong4ny/Refactoring/actions/workflows/msbuild.yml/badge.svg)](https://github.com/jabdong4ny/Refactoring/actions/workflows/msbuild.yml)

# VendingMachine

C++로 구현된 간단한 자판기 시뮬레이션 프로그램입니다. 
이 프로그램은 음료의 재고를 관리하고, 사용자가 음료를 구매할 수 있는 기능을 제공합니다.

## 주요 기능

- **재고 관리**: 관리자 모드에서 음료의 입고 및 출고를 관리할 수 있습니다.
- **사용자 구매**: 사용자 모드에서 음료를 선택하고 구매할 수 있습니다.
- **재고 현황 표시**: 현재 자판기에 있는 음료의 이름, 가격, 재고 수량을 확인할 수 있습니다.

## 프로젝트 구조

- `VendingMachine.cpp`: 프로그램의 메인 로직이 구현된 파일입니다.
- `CocaCola.h`, `Cider.h`: 음료 종류를 정의한 헤더 파일입니다.
- `data.h`: 데이터 초기화 및 관련 유틸리티를 포함합니다.

## 설치 및 실행 방법

1. 이 저장소를 클론합니다:
   git clone git@github.com:jabdong4ny/Refactoring.git
2. Visual Studio 2022에서 프로젝트를 엽니다.
3. 프로젝트를 빌드하고 실행합니다.

## 사용 방법

1. 프로그램을 실행하면 현재 자판기의 재고 현황이 표시됩니다.
2. 다음 옵션 중 하나를 선택합니다:
   - **관리자 모드 (1)**: 음료의 입고 및 출고를 관리합니다.
   - **사용자 모드 (2)**: 음료를 선택하고 구매합니다.
   - **종료 (0)**: 프로그램을 종료합니다.
3. 관리자 모드에서는 음료 이름과 수량을 입력하여 재고를 조정할 수 있습니다.
4. 사용자 모드에서는 음료 이름과 구매 수량을 입력하여 음료를 구매할 수 있습니다.

## 예제
== 재고 현황 == 
name    | price | ea  
Cider     1000    10  
CocaCola  1200    20  
관리자모드 1, 사용자 모드 2, 종료 0  
  
### 관리자 모드
•	입고 입력 1, 출고 입력 2, 나가기 3  
1  
입고 음료 : Cider  
입고 수량 : 5  
result = Cider 1000 15  

### 사용자 모드
관리자모드 1, 사용자 모드 2, 종료 0  
2  
구매 음료 : CocaCola  
구매 수량 : 2  
result = CocaCola 1200 18  
Cider 1000 15  
CocaCola 1200 18  

## 요구 사항
- C++14 이상
- Visual Studio 2022

## 기여
이 프로젝트에 기여하고 싶다면, 이 저장소를 포크하고 풀 리퀘스트를 보내주세요.