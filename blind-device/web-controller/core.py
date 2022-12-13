from selenium import webdriver
from selenium.webdriver.remote.webelement import WebElement
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.chrome.service import Service as ChromeService
from selenium.webdriver.common.keys import Keys
from webdriver_manager.chrome import ChromeDriverManager
from dataclasses import dataclass

chrome_options = Options()
chrome_options.add_experimental_option("debuggerAddress", "127.0.0.1:9222")
driver = webdriver.Chrome(service=ChromeService(ChromeDriverManager().install()), options=chrome_options)
driver.implicitly_wait(1)

driver.get('https://kiosk.krome0.com')


@dataclass
class Menu:
    menu_name: str
    menu_price: str
    menu_button: WebElement
    selected: bool = False


class RootController:
    def __init__(self):
        self.take_out_button = driver.find_element(By.XPATH, '/html/body/div/body/main/div[5]/div[1]/div[1]/a')
        self.store_button = driver.find_element(By.XPATH, '/html/body/div/body/main/div[5]/div[2]/div[1]/a')

    def click_take_out(self):
        self.take_out_button.send_keys('\n')

    def click_store_button(self):
        self.store_button.send_keys('\n')


class OrderController:
    def __init__(self):
        self._menu_list: list[Menu] = []
        for i in range(1, 10):
            try:
                menu = driver.find_element(By.XPATH, f'/html/body/div/body/div[3]/button[{i}]')
            except:
                break

            new_menu = Menu(
                menu.find_element(By.XPATH, 'div[1]').text,
                menu.find_element(By.XPATH, 'div[2]/div[2]').text,
                menu
            )

            self._menu_list.append(new_menu)

    def select_menu(self, number):
        if number > len(self._menu_list):
            return None

        number -= 1

        self._menu_list[number].menu_button.send_keys('\n')
        self._menu_list[number].selected = not self._menu_list[number].selected

    @property
    def menu_count(self):
        return len(self._menu_list)


if __name__ == '__main__':
    root_controller = RootController()
    root_controller.click_take_out()
    driver.implicitly_wait(3)

    order_controller = OrderController()
    order_controller.select_menu(2)
    order_controller.select_menu(1)
    order_controller.select_menu(3)
