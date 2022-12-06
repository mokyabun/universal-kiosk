from django.shortcuts import render
from .models import Stuff


# Create your views here.

def main(request):
    return render(request, 'kiosk-main-page.html')


def order(request):
    stuffs = Stuff.objects.all()
    context = {'stuffs': stuffs}
    return render(request, 'kiosk-order-page.html', context)
