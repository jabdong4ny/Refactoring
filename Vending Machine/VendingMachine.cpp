// VendingMachine.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include "data.h"
#include "Cider.h"
#include "CocaCola.h"


std::vector<sDrink> makeDefaultSet() {
    std::vector<sDrink> items;
    items.push_back({ Cider(), 1, 1000, 10 });
    items.push_back({ CocaCola(), 2, 1200, 20 });
    return items;
};

enum class Status
{
	INTRO, INVENTORY, MAIN_MODE, ADMIN_MODE, USER_MODE, INCOMING_INVENTORY, OUTGOING_INVENTORY, QUANTITY, ERROR, EXIT
};

Status printProcess(Status type, const std::vector<sDrink>& items) {
	switch (type) {
	case Status::INTRO:
		std::cout << "Welcome to the Vending Machine!" << std::endl;
		break;
	case Status::INVENTORY:
        std::cout << std::endl;
        std::cout << "== 재고 현황 ==" << std::endl;
        std::cout << "번호 | name | price | ea  " << std::endl;
        for (const auto& item : items) {
            std::cout << item.index << " " << item.name.getname() << " " << item.price << " " << item.inventory << std::endl;
        }
        std::cout << std::endl;
		break;
	case Status::MAIN_MODE:
		std::cout << "관리자모드 1, 사용자 모드 2, 종료 0" << std::endl;
		break;
	case Status::ADMIN_MODE:
		std::cout << "- 입고 입력 1, 출고 입력 2, 나가기 0" << std::endl;
		break;
	case Status::USER_MODE:
		std::cout << "구매 음료 번호 : ";
		break;

    case Status::INCOMING_INVENTORY:
        std::cout << "입고 음료 번호 : ";
        break;
	case Status::OUTGOING_INVENTORY:
		std::cout << "출고 음료 번호 : ";
		break;
	case Status::QUANTITY:
		std::cout << "수량 : ";
		break;
    case Status::ERROR:
        std::cout << "잘못된 입력입니다. 다시 시도하세요." << std::endl;
        break;

	case Status::EXIT:
		std::cout << "종료 합니다." << std::endl;
		break;
	}
    return type;
}

unsigned int inputProcess(Status type) {
    unsigned int input = 0;
    switch (type)
    {
    case Status::MAIN_MODE:
	case Status::ADMIN_MODE:
	case Status::USER_MODE:
	case Status::INCOMING_INVENTORY:
	case Status::OUTGOING_INVENTORY:
	case Status::QUANTITY:
		std::cin >> input;
		return input;
    default:
    //case Status::INTRO:
    //case Status::INVENTORY:
    //case Status::EXIT:
        break;
    }
    return 0;
}

Status logicProcess(const std::pair<Status, unsigned int>& p, std::vector<sDrink>& items) {
    unsigned int ea = 0;
    Status type = p.first;
    switch (type) {
    case Status::INTRO:
        type = Status::INVENTORY;
        break;
    case Status::INVENTORY:
        type = Status::MAIN_MODE;
        break;
    case Status::MAIN_MODE:
        switch (p.second) {
        case 1:
            type = Status::ADMIN_MODE;
            break;
        case 2:
            type = Status::USER_MODE;
            break;
        case 0:
            type = Status::EXIT;
            printProcess(Status::EXIT, items);
            break;
        default: printProcess(Status::ERROR, items);
            break;
        }
        break;

    case Status::ADMIN_MODE:
        switch (p.second) {
        case 1: // 입고
            type = Status::INCOMING_INVENTORY;
            break;
        case 2: // 출고
            type = Status::OUTGOING_INVENTORY;
            break;
        case 0: // 나가기
            type = Status::MAIN_MODE;
            break;
        default: printProcess(Status::ERROR, items); 
            break;
        }
        break;

    case Status::INCOMING_INVENTORY:
        printProcess(Status::QUANTITY, items);
        ea = inputProcess(Status::QUANTITY);
        for(auto& item : items) {
            if (item.index == p.second) {
                item.inventory += ea;
                printProcess(Status::INVENTORY, items);
                break;
            }
		}
        type = Status::ADMIN_MODE;
        break;

    case Status::OUTGOING_INVENTORY:
    case Status::USER_MODE:
        printProcess(Status::QUANTITY, items);
        ea = inputProcess(Status::QUANTITY);
        for(auto& item : items) {
            if (item.index == p.second) {
                int remain = item.inventory - ea;
                if (remain >= 0) {
                    item.inventory = remain;
                    printProcess(Status::INVENTORY, items);
                }
                else {
                    printProcess(Status::ERROR, items);
                    return type;
                }
            }
		}
        if(type == Status::OUTGOING_INVENTORY)
            type = Status::ADMIN_MODE;
		else
            type = Status::MAIN_MODE;
        break;
    }
    return type;
}

int main()
{
    //기본 값 셋팅
    auto items = makeDefaultSet();

    Status type = Status::INTRO;
    std::pair<Status, unsigned int> p = { type, 0 };

    while (true)
    {
		// 현재 상태에 따라 출력
        printProcess(type, items);

		// 입력 처리
        unsigned int input = inputProcess(type);
        p = { type, input };

		// 상태 전환 및 로직 처리
        type = logicProcess(p, items);

		// 종료 상태 확인
		if (type == Status::EXIT) {
			break;
		}
    }
    return 0;
}
