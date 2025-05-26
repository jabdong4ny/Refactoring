// VendingMachine.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include "data.h"
#include "Cider.h"
#include "CocaCola.h"


std::vector<sDrink> makeDefaultSet() {
    std::vector<sDrink> items;
    sDrink item;
    item.name = Cider();
    item.price = 1000;
    item.inventory = 10;
	item.index = items.size() + 1;
    items.push_back(item);

    item.name = CocaCola();
    item.price = 1200;
    item.inventory = 20;
    item.index = items.size() + 1;
    items.push_back(item);
    return items;
};

enum class status
{
	INTRO, INVENTORY, MAIN_MODE, ADMIN_MODE, USER_MODE, INCOMING_INVENTORY, OUTGOING_INVENTORY, QUANTITY, ERROR, EXIT
};

status printProcess(status type, const std::vector<sDrink>& items) {
	switch (type) {
	case status::INTRO:
		std::cout << "Welcome to the Vending Machine!" << std::endl;
		break;
	case status::INVENTORY:
        std::cout << std::endl;
        std::cout << "== 재고 현황 ==" << std::endl;
        std::cout << "번호 | name | price | ea  " << std::endl;
        for (auto item : items) {
            std::cout << item.index << " " << item.name.getname() << " " << item.price << " " << item.inventory << std::endl;
        }
        std::cout << std::endl;
		break;
	case status::MAIN_MODE:
		std::cout << "관리자모드 1, 사용자 모드 2, 종료 0" << std::endl;
		break;
	case status::ADMIN_MODE:
		std::cout << "- 입고 입력 1, 출고 입력 2, 나가기 0" << std::endl;
		break;
	case status::USER_MODE:
		std::cout << "구매 음료 번호 : ";
		break;

    case status::INCOMING_INVENTORY:
        std::cout << "입고 음료 번호 : ";
        break;
	case status::OUTGOING_INVENTORY:
		std::cout << "출고 음료 번호 : ";
		break;
	case status::QUANTITY:
		std::cout << "수량 : ";
		break;
    case status::ERROR:
        std::cout << "잘못된 입력입니다. 다시 시도하세요." << std::endl;
        break;

	case status::EXIT:
		std::cout << "종료 합니다." << std::endl;
		break;
	}

    return type;
}

unsigned int inputProcess(status type) {
    unsigned int input = 0;
    switch (type)
    {
    case status::INTRO:
    case status::INVENTORY:
    case status::EXIT:
        break;
    case status::MAIN_MODE:
	case status::ADMIN_MODE:
	case status::USER_MODE:
	case status::INCOMING_INVENTORY:
	case status::OUTGOING_INVENTORY:
	case status::QUANTITY:
		std::cin >> input;
		return input;
		break;

    default:
        break;
    }
}

status logicProcess(std::pair<status, unsigned int> p, std::vector<sDrink>& items) {
    unsigned int ea = 0;
    status type = p.first;
    switch (type) {
    case status::INTRO:
        type = status::INVENTORY;
        break;
    case status::INVENTORY:
        type = status::MAIN_MODE;
        break;
    case status::MAIN_MODE:
        switch (p.second) {
        case 1:
            type = status::ADMIN_MODE;
            break;
        case 2:
            type = status::USER_MODE;
            break;
        case 0:
            type = status::EXIT;
            printProcess(status::EXIT, items);
            break;
        default:
            std::cout << "잘못된 입력입니다. 다시 시도하세요." << std::endl;
            break;
        }
        break;

    case status::ADMIN_MODE:
        switch (p.second) {
        case 1: // 입고
            type = status::INCOMING_INVENTORY;
            break;
        case 2: // 출고
            type = status::OUTGOING_INVENTORY;
            break;
        case 0: // 나가기
            type = status::MAIN_MODE;
            break;
        default:
            std::cout << "잘못된 입력입니다. 다시 시도하세요." << std::endl;
            break;
        }
        break;

    case status::INCOMING_INVENTORY:
        printProcess(status::QUANTITY, items);
        ea = inputProcess(status::QUANTITY);
        for (int i = 0; i < items.size(); i++) {
            if (items[i].index == p.second) {
                items[i].inventory = items[i].inventory + ea;
                printProcess(status::INVENTORY, items);
                break;
            }
        }
        type = status::ADMIN_MODE;
        break;

    case status::OUTGOING_INVENTORY:
    case status::USER_MODE:
        printProcess(status::QUANTITY, items);
        ea = inputProcess(status::QUANTITY);
        for (int i = 0; i < items.size(); i++) {
            if (items[i].index == p.second) {
                int remain = items[i].inventory - ea;
                bool bPossible = (remain > 0) ? true : false;
                if (bPossible) {
                    items[i].inventory = remain;
                    printProcess(status::INVENTORY, items);
                }
                else {
                    printProcess(status::ERROR, items);
                    return type;
                }
            }
        }
        if(type == status::OUTGOING_INVENTORY)
            type = status::ADMIN_MODE;
		else
            type = status::MAIN_MODE;
        break;
    }
    return type;
}



int main()
{

    std::vector<sDrink> items;

    //기본 값 셋팅
    items = makeDefaultSet();

    auto type = status::INTRO;
    std::pair<status, unsigned int> p = { type, 0 };

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
		if (type == status::EXIT) {
			break;
		}
    }
}
