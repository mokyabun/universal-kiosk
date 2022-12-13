<script>
    import { onMount } from "svelte";
    import MenuItem from "./_menuItem.svelte";

    let menus = []
    
    onMount(async () => {
        const response = await fetch("https://api.krome0.com/api/menus")
        menus = response.status === 200 ? await response.json() : []
    });

    let totalPrice = 0

    function calculatePrice(event){
        if (event.detail.checked) totalPrice -= event.detail.menu.price
        else totalPrice += event.detail.menu.price
    }
</script>

<head>
    <meta charset="UTF-8">
</head>

<body>
    <div class="header_container">
        <div class="header_title_container">
            <div class="header_title">Universal</div>
            <div class="header_title">Kiosk</div>
        </div>
        <img src="/images/logo.png" alt="logo" class="header_logo_img">
    </div>

    <div class="payment_container">
        <div class="payment_title">총 주문금액</div>
        <div class="payment_price">
            <div id="total_price">{totalPrice}</div>
            <div>원</div>
        </div>
        <img class="payment_img" src="/images/shopping_cart.png" alt="shopping_cart">
    </div>

    <div class="menu_list_container">
        {#each menus as menu}
            <MenuItem {menu} on:selectMenu={calculatePrice} />
        {/each}
    </div>
</body>

<style>
    body {
        background-color: #002940;
        margin: 0;
        display: flex;
        flex-direction: column;
        font-family: Arial, Helvetica, sans-serif;
        height: 100vh;
    }

    .header_container {
        background-color: #006890;
        padding: 5px 10px;
        display: flex;
        flex-direction: row;
        color: white;
        justify-content: space-between;
        align-items: center;
    }

    .header_title_container {
        flex: 6;
    }

    .header_title {
        font-weight: 900;
        font-size: 6vh;
    }

    .header_logo_img {
        flex: 1;
        border-radius: 50%;
        /* border: solid white 10px; */
        text-align: center;
        width: 1px;
    }

    .payment_container {
        display: flex;
        flex-direction: row;
        color: white;
        font-weight: 700;
        align-items: center;
        justify-content: space-between;
        padding: 5px 10px 15px 10px;
    }

    .payment_title {
        flex: 5;
        font-size: 3vh;
    }

    .payment_price {
        flex: 1;
        display: flex;
        flex-direction: row;
        justify-content: right;
        align-items: center;
        margin-right: 1vh;
        font-size: 3vh;
    }

    .menu_list_container {
        padding: 10px 10px;
        background-color: white;
        margin: 0 10px;
        border-radius: 10px;

        display: grid;
        grid-template-columns: 1fr 1fr;
        gap: 15px;
    }
    
    .payment_img {
        width: 3vh;
        object-fit: contain;
    }
</style>