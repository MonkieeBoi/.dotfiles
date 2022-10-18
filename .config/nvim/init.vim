    let mapleader = ' '

" Basic Settings

    set encoding=utf-8
    set nu rnu
    set is
    set nohls
    syntax on
    set nocompatible
    set termguicolors
    set ignorecase smartcase

" Autocompletion

    set wildmode=longest,list,full
    filetype plugin on
    set omnifunc=syntaxcomplete#Complete
    " set shortmess+=c

" Tabs

    set tabstop=4
    set softtabstop=4
    set shiftwidth=4
    set expandtab
    set autoindent

" Splits

    set splitbelow splitright

" Clipboard

    " set clipboard+=unnamedplus


" Plugins

call plug#begin(stdpath('data') . '/plugged')

    " Plug 'shaunsingh/nord.nvim'
    Plug 'arcticicestudio/nord-vim'
    Plug 'itchyny/lightline.vim'
    Plug 'numToStr/Comment.nvim'
    Plug 'norcalli/nvim-colorizer.lua'
    Plug 'vimwiki/vimwiki'
    " Plug 'JoosepAlviste/nvim-ts-context-commentstring'

call plug#end()

" Theming

    let g:lightline = {'colorscheme': 'nord'}
    let g:nord_disable_background = v:true
    set laststatus=2
    colorscheme nord

" Keybinding

    " CTRL-C doesn't trigger the InsertLeave autocmd . map to <ESC> instead.
    inoremap <c-c> <ESC>

    " Use <TAB> to select the popup menu:
    inoremap <expr> <Tab> pumvisible() ? "\<C-n>" : "\<Tab>"
    inoremap <expr> <S-Tab> pumvisible() ? "\<C-p>" : "\<S-Tab>"

" Vimwiki

    let g:vimwiki_list = [{'path': '~/Documents/vimwiki'}]

" Cleanup
    :au VimLeave * set guicursor=a:ver25

lua << EOF
    require('Comment').setup()
    require 'colorizer'.setup()
    -- require'nvim-treesitter.configs'.setup {
    --     context_commentstring = {
    --     enable = true
    --     }
    -- }

EOF
