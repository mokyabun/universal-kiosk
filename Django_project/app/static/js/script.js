let total_price = document.getElementById("total_price");
let checkbox = document.getElementsByClassName("checkbox");

for(let chk of checkbox){
    chk.addEventListener('change', calculate_price)
}

function calculate_price(){
    let price = document.getElementById("price_" + this.id.substring(4)).innerHTML;
    if(this.checked) total_price.innerHTML = parseInt(total_price.innerHTML) + parseInt(price) + "";
    else total_price.innerHTML = parseInt(total_price.innerHTML) - parseInt(price) + "";
}