#include<iostream>
#include <algorithm> // Include this header for std::ranges::max to work properly

int main()
{

   std::cout << "well come to the VendingMachine!!\n";

   std::vector<sDrink> items;

   // 기본 값 셋팅
   items = makeDefaultSet();

   while (true)
   {
       unsigned int input = 0;
       std::cout << "== 재고 현황 ==" << std::endl;
       std::cout << "name | price | ea  " << std::endl;
       for (auto item : items) {
           std::cout << item.name.getname() << " " << item.price << " " << item.inventory << std::endl;
       }

       std::cout << "관리자모드 1, 사용자 모드 2, 종료 0" << std::endl;
       std::cin >> input;
       switch (input) {
       case 1: {
           while (true) {

               std::cout << "- 입고 입력 1, 출고 입력 2, 나가기 3" << std::endl;
               std::cin >> input;

               switch (input) {
               case 1: {
                   std::string inputname;
                   unsigned int num;
                   std::cout << "입고 음료 : ";
                   std::cin >> inputname;
                   std::cout << "입고 수량 : ";
                   std::cin >> num;
                   for (int i = 0; i < items.size(); i++) {
                       if ((items[i].name.getname()).compare(inputname) == 0) {
                           items[i].inventory = items[i].inventory + num;
                           std::cout << "result = " << items[i].name.getname() << " " << items[i].price << " " << items[i].inventory << std::endl;
                           break;
                       }
                   }
                   break;
               }

               case 2: {
                   std::string outputname;
                   unsigned int num;
                   std::cout << "출고 음료 : ";
                   std::cin >> outputname;
                   std::cout << "출고 수량 : ";
                   std::cin >> num;
                   for (int i = 0; i < items.size(); i++) {
                       if ((items[i].name.getname()).compare(outputname) == 0) {
                           items[i].inventory = items[i].inventory - num;
                           std::cout << "result = " << items[i].name.getname() << " " << items[i].price << " " << items[i].inventory << std::endl;
                           break;
                       }
                   }
                   break;
               }
               case 3: break;
               default: break;
               }
               if (input == 3) break;
           }
           break;
       };
       case 2: {
           while (true) {
               std::string buyname;
               unsigned int num;
               std::cout << "구매 음료 : ";
               std::cin >> buyname;
               std::cout << "구매 수량 :";
               std::cin >> num;
               for (int i = 0; i < items.size(); i++) {
                   if ((items[i].name.getname()).compare(buyname) == 0) {
                       items[i].inventory = items[i].inventory - num;
                       std::cout << "result = " << items[i].name.getname() << " " << items[i].price << " " << items[i].inventory << std::endl;
                       break;
                   }
               }
               break;
           }
       };
       case 3: break;
       default:
           break;
       }
       if (input == 0) break;
   }
}
