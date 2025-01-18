import os
import subprocess

# Caminhos para as pastas
pasta_entradas = "./input"
pasta_solucoes = "./solucoes"
programa = "./crush_grandes.c"  # Seu programa para resolver as instâncias

# Função para comparar os resultados
def comparar_resultados(saida_gerada, saida_esperada):
    print(f'ESPERADO: {saida_esperada}')
    print(f'GERADO: {saida_gerada}')
    return saida_gerada.strip() == saida_esperada.strip()

# Loop para testar cada instância
for arquivo_entrada in sorted(os.listdir(pasta_entradas)):
    if arquivo_entrada.endswith(".in"):
        nome_instancia = arquivo_entrada[:-3]  # Remove a extensão ".in"
        caminho_entrada = os.path.join(pasta_entradas, arquivo_entrada)
        caminho_saida = os.path.join(pasta_solucoes, f"{nome_instancia}.sol")
        
        # Verifica se o arquivo de solução correspondente existe
        if not os.path.exists(caminho_saida):
            print(f"{nome_instancia}: Arquivo de solução não encontrado ❌")
            continue
        
        # Ler a saída esperada
        with open(caminho_saida, "r") as f:
            saida_esperada = f.read()
        
        # Executar o programa
        resultado = subprocess.run(
            ["./crush_grandes"], 
            input=open(caminho_entrada, "r").read(),
            text=True,
            capture_output=True
        )
        
        # Comparar resultados
        if comparar_resultados(resultado.stdout, saida_esperada):
            print(f"{nome_instancia}: PASSED ✅\n")
        else:
            print(f"{nome_instancia}: FAILED ❌\n")
            print(f"Esperado:\n{saida_esperada}")
            print(f"Gerado:\n{resultado.stdout}")

