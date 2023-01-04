<script>
    import { base } from "$app/paths";
</script>

<head>
    <meta charset="UTF-8">
</head>
<body>
    <main>
        <div class="kiosk_title">Universal</div>
        <div class="kiosk_title">Kiosk</div>
        <div class="dummy_div"></div>
        <div class="qr_container">
            <div class="container_title">Web Order</div>
            <img src="/images/QR.png" alt="QR_code" class="qr_img">
        </div>
        <div class="choice_container">
            <div class="opt_container">
                <div class="img_container">
                    <a href="/order"> <img src="/images/takeout_button.png" alt="takeout_button" class="opt1_img"> </a>
                </div>
                <div class="container_title">Take Out</div>
            </div>
            <div class="opt_container">
                <div class="img_container">
                    <a href="/order"> <img src="/images/shop_button.png" alt="shop_button" class="opt2_img"> </a>
                </div>
                <div class="container_title">Eat In</div>
            </div>
        </div>
    </main>
</body>

<style>
    body {
        background-color: #006890;
        margin: 0;
        padding: 0;
        display: flex;
        flex-direction: column;
        font-family: Arial, Helvetica, sans-serif;
        height: 100vh;
    }

    main {
        margin: 0;
        padding: 10% 5%;
    }

    .kiosk_title {
        color: white;
        font-weight: 900;
        font-size: 9vh;
    }

    .container_title {
        color: white;
        font-weight: 600;
        font-size: 2vh;
        margin: 6px;
    }

    .dummy_div {
        padding-top: 15vh;
    }

    .qr_container {
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        margin-bottom: 5vh;
    }

    .qr_img {
        width: 20vh;
    }

    .choice_container {
        display: flex;
        flex-direction: row;
        justify-content: center;
    }

    .opt_container {
        display: flex;
        flex-direction: column;
        align-items: center;
        width: 20vh;
    }

    .opt1_img {
        width: 70%;
        border-radius: 15px;
    }

    .opt2_img {
        width: 70%;
        border-radius: 15px;
    }

    a {
        all: unset;
    }

    a:hover {
        cursor: pointer;
    }

    .img_container {
        text-align: center;
    }
</style>