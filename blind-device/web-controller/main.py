from serial import Serial
from core import RootController, OrderController


def main():
    serial = Serial(port='<ADD PORT>', baudrate=9600)
    root_controller = RootController()
    is_root = True

    while is_root:
        if serial.readable():
            data = int(serial.readline())
            print(f'Data: {data}')
            if data == 1:
                root_controller.click_take_out()
                is_root = False

            if data == 0:
                root_controller.click_store_button()
                is_root = False

    order_controller = OrderController()
    is_order = True

    while is_order:
        if serial.readable():
            data = int(serial.readline())
            print(f'Data: {data}')
            if data <= order_controller.menu_count:
                order_controller.select_menu(data)
            else:
                print('Number too big!')


if __name__ == '__main__':
    main()
