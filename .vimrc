" Basic Settings

    set encoding=utf-8
    set nu rnu
    set is
    set nohls
    syntax on
    set nocompatible
    set ignorecase smartcase

" Autocompletion

    set wildmode=longest,list,full
    filetype plugin on

" Tabs

    set tabstop=4
    set softtabstop=4
    set shiftwidth=4
    set expandtab
    set autoindent

" Splits

    set splitbelow splitright

" Theming

    let g:lightline = {'colorscheme': 'nord'}
    set laststatus=2
    colorscheme nord
